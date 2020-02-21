#ifndef MAXIMIZE_ACTION_HPP
#define MAXIMIZE_ACTION_HPP

#include "action.hpp"

#include "rule/rule_interface.hpp"

class maximize_action_t : public action_t
{
public:
    maximize_action_t();
    virtual ~maximize_action_t() override;

    virtual bool execute(rule_interface_t &interface) override;
};

#endif // MAXIMIZE_ACTION_HPP
