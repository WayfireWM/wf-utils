#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstddef>
#include <set>
#include <string>
#include <string_view>
#include <vector>

#include "literal.hpp"
#include "symbol.hpp"

static const std::set<std::string_view> DELIMITERS = {" ", "\'", "\""};

class lexer_t
{
public:
    lexer_t();
    lexer_t(const std::string &text);
    void reset();
    void reset(const std::string &text);

    symbol_t parse_symbol();
    void reverse();

    const std::string &current_line() const;
    std::size_t current_line_number() const;
    std::size_t current_symbol_position() const;
private:
    void _next_line();
    void _tokenize(const std::string &text);
    literal_t _parse_literal(const std::string &line, std::size_t size);
    literal_t _parse_encapsulated_literal(const std::string &line, const std::string &s_bound, const std::string &e_bound, std::size_t size);
    literal_t _parse_comment_literal(const std::string &line, std::size_t size);

    std::vector<std::string> _lines;

    bool _started;
    bool _ended;

    std::size_t _line_number;
    std::size_t _parse_position;
    std::size_t _symbol_position;
};

#endif // LEXER_HPP
