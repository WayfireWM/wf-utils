#include "maximize_action.hpp"

#include "action.hpp"

#include "rule/rule_interface.hpp"

maximize_action_t::maximize_action_t() : action_t()
{
}

maximize_action_t::~maximize_action_t()
{
}

bool maximize_action_t::execute(rule_interface_t &interface)
{
    return interface.maximize();
}
