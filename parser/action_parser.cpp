#include "action_parser.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <variant>

#include "action/maximize_action.hpp"
#include "action/minimize_action.hpp"
#include "action/set_action.hpp"
#include "lexer/lexer.hpp"
#include "lexer/symbol.hpp"

std::shared_ptr<action_t> action_parser_t::parse(lexer_t &lexer)
{
    auto symbol = lexer.parse_symbol();
    if (symbol.type != symbol_t::type_t::ACTION)
    {
        throw std::runtime_error("Action parser error. Expected action.");
    }

    auto action = std::get<std::string>(symbol.value);
    if (action == "set")
    {
        return _parse_set_action(lexer);
    }
    else if (action == "maximize")
    {
        return std::make_shared<maximize_action_t>();
    }
    else if (action == "minimize")
    {
        return std::make_shared<minimize_action_t>();
    }
    else
    {
        std::string error = "Action parser error. Unsupported action specified. action: ";
        error.append(action);
        throw std::runtime_error(error);
    }
}

std::shared_ptr<action_t> action_parser_t::_parse_set_action(lexer_t &lexer)
{
    auto symbol = lexer.parse_symbol();
    if (symbol.type != symbol_t::type_t::IDENTIFIER)
    {
        throw std::runtime_error("Action parser error. Expected identifier.");
    }
    auto identifier = std::get<std::string>(symbol.value);

    symbol = lexer.parse_symbol();
    if (symbol.type != symbol_t::type_t::LITERAL)
    {
        throw std::runtime_error("Action parser error. Expected literal.");
    }
    auto value = symbol.value;

    return std::make_shared<set_action_t>(identifier, value);
}
