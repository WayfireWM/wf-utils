#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstddef>
#include <set>
#include <string>
#include <string_view>

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

    const std::string &text() const;
    std::size_t current_symbol_position() const;
private:
    literal_t _parse_literal();
    literal_t _parse_encapsulated_literal(const std::string &s_bound, const std::string &e_bound);
    literal_t _parse_comment_literal();

    std::size_t _size;
    std::string _text;

    std::size_t _parse_position;
    std::size_t _symbol_position;
};

#endif // LEXER_HPP
