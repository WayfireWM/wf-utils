#ifndef ACTION_HPP
#define ACTION_HPP

#include "variant.hpp"
#include <string>
#include <vector>

namespace wf
{

class rule_interface_t;

/**
 * @brief The action_t class describes an action to be executed on positive or negative match of a condition.
 */
class action_t
{
public:
    /**
     * @brief action_t Constructs an action.
     *
     * @param[in] name Name of the command to execute.
     * @param[in] args Argemts for the command to execute.
     */
    action_t(const std::string &name, const std::vector<variant_t> &args);

    /**
     * @brief execute Executes the command in the action.
     *
     * @param[in] interface The rule interface to use to access the object being handled.
     *
     * @return <code>True</code> if an error occurred, <code>false</code> if not.
     */
    bool execute(rule_interface_t &interface);
private:
    /**
     * @brief _name Name of the command to execute.
     */
    std::string _name;

    /**
     * @brief _args Arguments for the command to execute.
     */
    std::vector<variant_t> _args;
};

} // End namespace wf.

#endif // ACTION_HPP
