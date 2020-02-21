#ifndef ACTION_HPP
#define ACTION_HPP

#include "rule/rule_interface.hpp"

class action_t
{
public:
    action_t();
    virtual ~action_t();

    /**
     * @brief execute
     * @param interface
     * @return <code>True</code> if an error occurred, <code>false</code> if not.
     */
    virtual bool execute(rule_interface_t &interface) = 0;
};

#endif // ACTION_HPP
