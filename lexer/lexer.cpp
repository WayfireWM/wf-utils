#include "lexer.hpp"

#include <cstddef>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "literal.hpp"
#include "symbol.hpp"
#include "utils.hpp"

lexer_t::lexer_t()
{
    reset("");
}

lexer_t::lexer_t(const std::string &text)
{
    reset(text);
}

void lexer_t::reset()
{
    _started = false;
    _ended = false;
    _line_number = 0;
    _parse_position = 0;
    _symbol_position = 0;
    _next_line();
}

void lexer_t::reset(const std::string &text)
{
    _started = false;
    _ended = false;
    _line_number = 0;
    _parse_position = 0;
    _symbol_position = 0;
    _tokenize(text);
    _next_line();
}

symbol_t lexer_t::parse_symbol()
{
    if (_ended)
    {
        return symbol_t(symbol_t::type_t::END_OF_TEXT);
    }

    const auto &line = _lines.at(_line_number);
    auto size = line.size();

    if (_parse_position >= size)
    {
        _next_line();
        return symbol_t(symbol_t::type_t::END_OF_LINE);
    }

    while (std::isspace(line.at(_parse_position)))
    {
        ++_parse_position;
    }

    _symbol_position = _parse_position;

    return symbol_t(_parse_literal(line, size));
}

void lexer_t::reverse()
{
    _parse_position = _symbol_position;
}

const std::string &lexer_t::current_line() const {
    return _lines.at(_line_number);
}

std::size_t lexer_t::current_line_number() const {
    return _line_number;
}

std::size_t lexer_t::current_symbol_position() const {
    return _symbol_position;
}

void lexer_t::_next_line()
{
    if (_ended)
    {
        return;
    }

    if (_started)
    {
        ++_line_number;
        _parse_position = 0;
    }
    else
    {
        _started = true;
    }

    if (_line_number >= _lines.size())
    {
        _ended = true;
    }
    else
    {
        // Starting a new line, find the start position.
        const auto &line = _lines.at(_line_number);
        auto size = line.size();
        while ((_parse_position < size) && (std::isspace(line.at(_parse_position))))
        {
            ++_parse_position;
        }
        _symbol_position = _parse_position;
    }
}

void lexer_t::_tokenize(const std::string &text)
{
    _lines.clear();

    if (!text.empty())
    {
        std::stringstream ss(text);
        std::string line;

        while (std::getline(ss, line, '\n'))
        {
            rtrim(line); // Only right trim, not left trim. Need to be able to show the line as is in error messages.
            _lines.push_back(line);
        }
    }
}

literal_t lexer_t::_parse_literal(const std::string &line, std::size_t size)
{
    // Catch out char and string literals first.
    auto c = line.substr(_parse_position, 1);
    if ((c == "\'") || (c == "\""))
    {
        return _parse_encapsulated_literal(line, c, c, size);
    }

    // It is possible that the literal is 1 character long (Structures and operators).
    if ((contains(OPERATORS, c)) || (contains(STRUCTURES, c)))
    {
         ++_parse_position;
        return literal_t(c);
    }

    // A literal is denoted from _position until the first occurrence of one of ')', '(', '&', '|', '!', ' ', '"', '\''
    auto end = std::string::npos;
    for (const auto &s : OPERATORS)
    {
        end = std::min(end, line.find(s, _parse_position));
    }
    for (const auto &s : STRUCTURES)
    {
        end = std::min(end, line.find(s, _parse_position));
    }
    for (const auto &s : DELIMITERS)
    {
        end = std::min(end, line.find(s, _parse_position));
    }

    // If we found none of them, the literal ends at the end of _text
    if (end == std::string::npos)
    {
        end = size;
    }

    // At this point we know that the literal we want is between _parse_position and end. Extract and return.
    auto length = end - _parse_position;
    auto literal_text = line.substr(_parse_position, length);
    _parse_position += length;
    return literal_t(literal_text);
}

literal_t lexer_t::_parse_encapsulated_literal(const std::string &line, const std::string &s_bound, const std::string &e_bound, std::size_t size)
{
    // Check if the boundary is at the end of the of the line.
    auto begin = _parse_position + s_bound.size();
    if (begin >= size)
    {
        _parse_position = size;
        throw std::runtime_error("Lexical parser error. Encapsulated literal is truncated.");
    }

    // Find the next occurrence of the boundary. Avoid escaped ones (\boundary).
    std::size_t found_at = 0;
    auto found = false;
    while (!found)
    {
        auto p = line.find(e_bound, begin);
        if (p == std::string::npos)
        {
            // Not found before end of line, complain and bail out.
            _parse_position = size;
            throw std::runtime_error("Lexical parser error. Encapsulated literal is truncated.");
        }

        // check the character before the boundary match to see if it is not an escape.
        if (line.at(p - 1) != '\\')
        {
            found = true;
            found_at = p;
            break;
        }
    }

    // If we get here, and found == false, it must mean that all the matches were escaped -> trunctated.
    if (!found)
    {
        _parse_position = size;
        throw std::runtime_error("Lexical parser error. Encapsulated literal is truncated.");
    }

    // Found a good match. The string we want is between _parse_position and (found_at + boundary_length)
    auto length = (found_at + e_bound.size()) - _parse_position;
    auto literal_text = line.substr(_parse_position, length);
    _parse_position += length;
    return literal_t(literal_text);
}

literal_t lexer_t::_parse_comment_literal(const std::string &line, std::size_t size)
{
    // Comment literal runs from the comment sign to the end of the line.
    auto literal_text = line.substr(_parse_position);
    _parse_position = size;
    return literal_t(literal_text);
}
