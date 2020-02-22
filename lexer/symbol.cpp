#include "symbol.hpp"

#include <set>
#include <stdexcept>
#include <string>
#include <string_view>

#include "literal.hpp"
#include "utils.hpp"

symbol_t::symbol_t(type_t t) : type(t), literal_type(literal_t::type_t::STRING), value("")
{
}

symbol_t::symbol_t(const literal_t &literal) : type(type_t::LITERAL), literal_type(literal.type), value(literal.value)
{
    // String literals can also be keywords, comments or identifiers. Check for this.
    if (literal.type == literal_t::type_t::STRING)
    {
        auto literal_value = std::get<std::string>(literal.value);

        if ((literal_value.front() == '\"') && (literal_value.back() == '\"'))
        {
            value = literal_value.substr(1, literal_value.size() - 2); // Strip quotes here.
        }
        else if (contains(SIGNALS, literal_value))
        {
            type = type_t::SIGNAL;
        }
        else if (contains(KEYWORDS, literal_value))
        {
            type = type_t::KEYWORD;
        }
        else if (contains(STRUCTURES, literal_value))
        {
            type = type_t::STRUCTURAL;
        }
        else if (contains(OPERATORS, literal_value))
        {
            type = type_t::OPERATOR;
        }
        else
        {
            bool first = true;
            for (const auto &c : literal_value)
            {
                auto digit = std::isdigit(c);
                auto letter = std::isalpha(c);
                auto underscore = (c == '_');

                if (first)
                {
                    first = false;
                    if (digit)
                    {
                        std::string error = "Symbol parser error. Identifier should start with _ or letter. text:";
                        error.append(literal_value);
                        throw std::runtime_error(error);
                    }
                }

                if (!(digit | letter | underscore))
                {
                    std::string error = "Symbol parser error. Identifier contains invalid character. text:";
                    error.append(literal_value);
                    throw std::runtime_error(error);
                }
            }
            type = type_t::IDENTIFIER;
        }
    }
}

std::string symbol_t::to_string() const
{
    std::string out = "Symbol [";
    switch (type)
    {
    case type_t::END:
        out.append("END");
        break;
    case type_t::IDENTIFIER:
        out.append("Identifier: ").append(std::get<std::string>(value));
        break;
    case type_t::LITERAL:
        out.append("Literal: [");
        switch (literal_type)
        {
        case literal_t::type_t::INT:
            out.append("int: ").append(std::to_string(std::get<int>(value)));
            break;
        case literal_t::type_t::CHAR:
            out.append("char: ").append(std::to_string(std::get<char>(value)));
            break;
        case literal_t::type_t::BOOL:
            out.append("bool: ").append(std::get<bool>(value) ? "true" : "false");
            break;
        case literal_t::type_t::FLOAT:
            out.append("float: ").append(std::to_string(std::get<float>(value)));
            break;
        case literal_t::type_t::DOUBLE:
            out.append("double: ").append(std::to_string(std::get<double>(value)));
            break;
        case literal_t::type_t::STRING:
            out.append("string: ").append(std::get<std::string>(value));
            break;
        }
        out.append("]");
        break;
    case type_t::OPERATOR:
        out.append("Operator: ").append(std::get<std::string>(value));
        break;
    case type_t::KEYWORD:
        out.append("Keyword: ").append(std::get<std::string>(value));
        break;
    case type_t::STRUCTURAL:
        out.append("Structural: ").append(std::get<std::string>(value));
        break;
    case type_t::SIGNAL:
        out.append("Signal: ").append(std::get<std::string>(value));
        break;
    }
    out.append("]");
    return out;
}
