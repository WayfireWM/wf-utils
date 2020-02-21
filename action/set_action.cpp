#include "set_action.hpp"

#include <string>

#include "action.hpp"

#include "lexer/symbol.hpp"
#include "rule/rule_interface.hpp"

set_action_t::set_action_t(const std::string &identifier, const symbol_t::value_t &value) : action_t(),_identifier(identifier), _value(value)
{
}

set_action_t::~set_action_t()
{
}

bool set_action_t::execute(rule_interface_t &interface)
{
    return interface.set(_identifier, _value);
}
