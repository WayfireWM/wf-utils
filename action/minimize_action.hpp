#ifndef MINIMIZE_ACTION_HPP
#define MINIMIZE_ACTION_HPP

#include "action.hpp"

#include "rule/rule_interface.hpp"

class minimize_action_t : public action_t
{
public:
    minimize_action_t();
    virtual ~minimize_action_t() override;

    virtual bool execute(rule_interface_t &interface) override;
};

#endif // MINIMIZE_ACTION_HPP
