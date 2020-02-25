#ifndef RULE_HPP
#define RULE_HPP

#include <memory>
#include <string>

namespace wf
{

class action_t;
class condition_t;
class rule_interface_t;

/**
 * @brief The rule_t class
 */
class rule_t
{
public:
    /**
     * @brief rule_t
     *
     * @param signal
     * @param condition
     * @param if_action
     * @param else_action
     */
    rule_t(const std::string &signal,
           std::shared_ptr<condition_t> condition,
           std::shared_ptr<action_t> if_action,
           std::shared_ptr<action_t> else_action);

    /**
     * @brief apply
     *
     * @param signal
     *
     * @return <code>True</code> if there was an error, <code>false</code> if not.
     */
    bool apply(const std::string &signal, rule_interface_t &interface);
private:
    std::string _signal;
    std::shared_ptr<condition_t> _condition;
    std::shared_ptr<action_t> _if_action;
    std::shared_ptr<action_t> _else_action;
};

} // End namespace wf.

#endif // RULE_HPP
