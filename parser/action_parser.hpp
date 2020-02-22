#ifndef ACTION_PARSER_HPP
#define ACTION_PARSER_HPP

#include <memory>

class action_t;
class lexer_t;

class action_parser_t {
public:
    std::shared_ptr<action_t> parse(lexer_t &lexer);
};

#endif // ACTION_PARSER_HPP
