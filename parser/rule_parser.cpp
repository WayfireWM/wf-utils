#include "rule_parser.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>

#include "action_parser.hpp"
#include "condition_parser.hpp"

#include "action/action.hpp"
#include "condition/condition.hpp"
#include "lexer/lexer.hpp"
#include "lexer/symbol.hpp"
#include "rule/rule.hpp"

std::shared_ptr<rule_t> rule_parser_t::parse(const std::string &text)
{
    lexer_t lexer(text);
    return parse(lexer);
}

std::shared_ptr<rule_t> rule_parser_t::parse(lexer_t &lexer)
{
    std::string signal;
    std::shared_ptr<condition_t> condition;
    std::shared_ptr<action_t> if_action;
    std::shared_ptr<action_t> else_action;

    try
    {
        // Expect the first symbol to be the 'on' keyword.
        auto symbol = lexer.parse_symbol();
        if ((symbol.type != symbol_t::type_t::KEYWORD) || (std::get<std::string>(symbol.value) != "on"))
        {
            throw std::runtime_error("Rule parser error. Expected 'on' keyword.");
        }

        // Expect a signal next.
        symbol = lexer.parse_symbol();
        if (symbol.type != symbol_t::type_t::SIGNAL)
        {
            throw std::runtime_error("Rule parser error. Expected signal.");
        }
        signal = std::get<std::string>(symbol.value);

        // Expect the 'if' keyword next.
        symbol = lexer.parse_symbol();
        if ((symbol.type != symbol_t::type_t::KEYWORD) || (std::get<std::string>(symbol.value) != "if"))
        {
            throw std::runtime_error("Rule parser error. Expected 'if' keyword.");
        }

        // Delegate to logical condition parser.
        condition = condition_parser_t().parse(lexer);

        // Expect the next symbol to be the 'then' keyword.
        symbol = lexer.parse_symbol();
        if ((symbol.type != symbol_t::type_t::KEYWORD) || (std::get<std::string>(symbol.value) != "then"))
        {
            throw std::runtime_error("Rule parser error. Expected 'then' keyword.");
        }

        // Delegate to action parser.
        if_action = action_parser_t().parse(lexer);

        // Check if there is an else symbol.
        symbol = lexer.parse_symbol();
        if (symbol.type == symbol_t::type_t::KEYWORD)
        {
            if (std::get<std::string>(symbol.value) != "else")
            {
                throw std::runtime_error("Rule parser error. Expected 'else' keyword.");
            }

            // Delegate to action parser.
            else_action = action_parser_t().parse(lexer);

            // Advance to next symbol. Expect EOL.
            symbol = lexer.parse_symbol();
        }

        // Expect END.
        if (symbol.type != symbol_t::type_t::END)
        {
            std::string error = "Rule parser error. Unexpected symbol: ";
            error.append(symbol.to_string());
            throw std::runtime_error(error);
        }
    }
    catch (std::runtime_error &e)
    {
        std::cout << "Malformed input:" << std::endl;
        std::cout << lexer.text() << std::endl;
        std::string pad;
        auto pos = lexer.current_symbol_position();
        for (std::size_t i = 0; i < pos; ++i)
        {
            pad.append(" ");
        }
        pad.append("^ ");
        std::cout << pad << e.what() << std::endl;
    }

    return std::make_shared<rule_t>(signal, condition, if_action, else_action);
}
