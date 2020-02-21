#ifndef CONDITION_PARSER_HPP
#define CONDITION_PARSER_HPP

#include <memory>

#include "condition/condition.hpp"
#include "lexer/lexer.hpp"

class condition_parser_t {
public:
    std::shared_ptr<condition_t> parse(lexer_t &lexer);
};

#endif // CONDITION_PARSER_HPP
