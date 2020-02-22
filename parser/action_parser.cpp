#include "action_parser.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <variant>

#include "action/action.hpp"
#include "lexer/lexer.hpp"
#include "lexer/symbol.hpp"

std::shared_ptr<action_t> action_parser_t::parse(lexer_t &lexer)
{
    auto symbol = lexer.parse_symbol();
    if (symbol.type != symbol_t::type_t::IDENTIFIER)
    {
        throw std::runtime_error("Action parser error. Expected identifier.");
    }
    auto name = std::get<std::string>(symbol.value);

    std::vector<symbol_t::value_t> args;
    auto done = false;
    while (!done)
    {
        symbol = lexer.parse_symbol();
        if ((symbol.type == symbol_t::type_t::LITERAL) || (symbol.type == symbol_t::type_t::IDENTIFIER))
        {
            args.push_back(symbol.value);
        }
        else
        {
            done = true;
            if (symbol.type != symbol_t::type_t::END)
            {
                lexer.reverse();
            }
        }
    }

    return std::make_shared<action_t>(name, args);
}
