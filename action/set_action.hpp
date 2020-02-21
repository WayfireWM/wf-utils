#ifndef SET_ACTION_HPP
#define SET_ACTION_HPP

#include <string>

#include "action.hpp"

#include "lexer/symbol.hpp"
#include "rule/rule_interface.hpp"

class set_action_t : public action_t
{
public:
    set_action_t(const std::string &identifier, const symbol_t::value_t &value);
    virtual ~set_action_t() override;

    virtual bool execute(rule_interface_t &interface) override;
private:
    std::string _identifier;
    symbol_t::value_t _value;
};

#endif // SET_ACTION_HPP
