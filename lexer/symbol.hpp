#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include "variant.hpp"
#include <set>
#include <string>
#include <string_view>

namespace wf
{

static const std::set<std::string_view> SIGNALS = {"created"};
static const std::set<std::string_view> KEYWORDS = {"equals", "contains", "if", "else", "then", "on"};
static const std::set<std::string_view> OPERATORS = {"&", "|", "!"};
static const std::set<std::string_view> STRUCTURES = {"(", ")"};

class symbol_t
{
public:
    enum class type_t
    {
        END,
        IDENTIFIER,
        LITERAL,
        OPERATOR,
        KEYWORD,
        STRUCTURAL,
        SIGNAL,
    };

    symbol_t();
    symbol_t(type_t t);
    symbol_t(const variant_t &v);

    type_t type;
    variant_t value;
};

std::string to_string(const symbol_t &s);

} // End namespace wf.

#endif // SYMBOL_HPP
