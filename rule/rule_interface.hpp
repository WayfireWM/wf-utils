#ifndef RULE_INTERFACE_HPP
#define RULE_INTERFACE_HPP

#include <string>
//#include <vector>

#include "lexer/symbol.hpp"

class rule_interface_t
{
public:
    virtual ~rule_interface_t();
    virtual symbol_t::value_t get(const std::string &identifier, bool &error) = 0;
    virtual bool set(const std::string &identifier, const symbol_t::value_t &value) = 0;
    virtual bool maximize() = 0;
    virtual bool minimize() = 0;

//    virtual bool action(const std::string &name, const std::vector<const symbol_t::value_t> &arguments) = 0;
};

#endif // RULE_INTERFACE_HPP
