#include "minimize_action.hpp"

#include "action.hpp"

#include "rule/rule_interface.hpp"

minimize_action_t::minimize_action_t() : action_t()
{
}

minimize_action_t::~minimize_action_t()
{
}

bool minimize_action_t::execute(rule_interface_t &interface)
{
    return interface.minimize();
}
