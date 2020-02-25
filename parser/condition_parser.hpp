#ifndef CONDITION_PARSER_HPP
#define CONDITION_PARSER_HPP

#include "lexer/symbol.hpp"
#include <memory>

namespace wf
{

class condition_t;
class lexer_t;

class condition_parser_t {
public:
    condition_parser_t();
    std::shared_ptr<condition_t> parse(lexer_t &lexer);
private:
    void _expression(lexer_t &lexer);
    void _term(lexer_t &lexer);
    void _factor(lexer_t &lexer);

    std::shared_ptr<condition_t> _root;
    symbol_t _symbol;
};

} // End namespace wf.

#endif // CONDITION_PARSER_HPP
