#ifndef ACTION_PARSER_HPP
#define ACTION_PARSER_HPP

#include <memory>

#include "action/action.hpp"

#include "lexer/lexer.hpp"

class action_parser_t {
public:
    std::shared_ptr<action_t> parse(lexer_t &lexer);
private:
    std::shared_ptr<action_t> _parse_set_action(lexer_t &lexer);
};

#endif // ACTION_PARSER_HPP
