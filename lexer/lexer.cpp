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
    _parse_position = 0;
    _symbol_position = 0;
}

void lexer_t::reset(const std::string &text)
{
    reset();
    _text = text;
    _size = text.size();
}

symbol_t lexer_t::parse_symbol()
{
    if (_parse_position >= _size)
    {
        return symbol_t(symbol_t::type_t::END);
    }

    while (std::isspace(_text.at(_parse_position)))
    {
        ++_parse_position;
    }

    _symbol_position = _parse_position;

    return symbol_t(_parse_literal());
}

void lexer_t::reverse()
{
    _parse_position = _symbol_position;
}

const std::string &lexer_t::text() const {
    return _text;
}

std::size_t lexer_t::current_symbol_position() const {
    return _symbol_position;
}

literal_t lexer_t::_parse_literal()
{
    // Catch out char and string literals first.
    auto c = _text.substr(_parse_position, 1);
    if ((c == "\'") || (c == "\""))
    {
        return _parse_encapsulated_literal(c, c);
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
        end = std::min(end, _text.find(s, _parse_position));
    }
    for (const auto &s : STRUCTURES)
    {
        end = std::min(end, _text.find(s, _parse_position));
    }
    for (const auto &s : DELIMITERS)
    {
        end = std::min(end, _text.find(s, _parse_position));
    }

    // If we found none of them, the literal ends at the end of _text
    if (end == std::string::npos)
    {
        end = _size;
    }

    // At this point we know that the literal we want is between _parse_position and end. Extract and return.
    auto length = end - _parse_position;
    auto literal_text = _text.substr(_parse_position, length);
    _parse_position += length;
    return literal_t(literal_text);
}

literal_t lexer_t::_parse_encapsulated_literal(const std::string &s_bound, const std::string &e_bound)
{
    // Check if the boundary is at the end of the of the line.
    auto begin = _parse_position + s_bound.size();
    if (begin >= _size)
    {
        _parse_position = _size;
        throw std::runtime_error("Lexical parser error. Encapsulated literal is truncated.");
    }

    // Find the next occurrence of the boundary. Avoid escaped ones (\boundary).
    std::size_t found_at = 0;
    auto found = false;
    while (!found)
    {
        auto p = _text.find(e_bound, begin);
        if (p == std::string::npos)
        {
            // Not found before end of line, complain and bail out.
            _parse_position = _size;
            throw std::runtime_error("Lexical parser error. Encapsulated literal is truncated.");
        }

        // check the character before the boundary match to see if it is not an escape.
        if (_text.at(p - 1) != '\\')
        {
            found = true;
            found_at = p;
            break;
        }
    }

    // If we get here, and found == false, it must mean that all the matches were escaped -> trunctated.
    if (!found)
    {
        _parse_position = _size;
        throw std::runtime_error("Lexical parser error. Encapsulated literal is truncated.");
    }

    // Found a good match. The string we want is between _parse_position and (found_at + boundary_length)
    auto length = (found_at + e_bound.size()) - _parse_position;
    auto literal_text = _text.substr(_parse_position, length);
    _parse_position += length;
    return literal_t(literal_text);
}

literal_t lexer_t::_parse_comment_literal()
{
    // Comment literal runs from the comment sign to the end of the line.
    auto literal_text = _text.substr(_parse_position);
    _parse_position = _size;
    return literal_t(literal_text);
}
