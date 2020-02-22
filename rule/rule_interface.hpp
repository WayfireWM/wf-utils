#ifndef RULE_INTERFACE_HPP
#define RULE_INTERFACE_HPP

#include <string>
#include <vector>

#include "lexer/symbol.hpp"

class rule_interface_t
{
public:
    virtual ~rule_interface_t();
    virtual symbol_t::value_t get(const std::string &identifier, bool &error) = 0;
    virtual bool execute(const std::string &name, const std::vector<symbol_t::value_t> &args) = 0;
};

#endif // RULE_INTERFACE_HPP
