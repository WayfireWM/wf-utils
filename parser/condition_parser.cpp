#include "condition_parser.hpp"

#include <memory>

#include "condition/condition.hpp"
#include "lexer/lexer.hpp"
#include "lexer/symbol.hpp"

std::shared_ptr<condition_t> condition_parser_t::parse(lexer_t &lexer)
{
    while (true)
    {
        auto symbol = lexer.parse_symbol();
        if ((symbol.type == symbol_t::type_t::KEYWORD) && (std::get<std::string>(symbol.value) == "then"))
        {
            lexer.reverse();
            break;
        }
    }

    return std::make_shared<condition_t>();
}
