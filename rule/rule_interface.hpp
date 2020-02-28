#ifndef RULE_INTERFACE_HPP
#define RULE_INTERFACE_HPP

#include "variant.hpp"
#include <string>
#include <vector>

namespace wf
{

/**
 * @brief The rule_interface_t class describes an interface that can be used by the rule system to evaluate conditions
 *        and execute actions.
 *
 * This intent of the rule system is that the user subclasses the interface and gives it the needed smarts to act on
 * the object type it is meant for.
 *
 * The responsabilities of an interface are to supply property values for the condition checking and execute named
 * actions on the object instance operated on.
 *
 * The rule system is intended to be generic, but it will require an implementation of an interface for EACH object
 * type the rules are supposed to work on. Implementing the interface is the user of the rule system's responsibility.
 */
class rule_interface_t
{
public:
    /**
     * @brief ~rule_interface_t Destructor.
     */
    virtual ~rule_interface_t();

    /**
     * @brief get Retrieves the value of a named property.
     *
     * @param[in] identifier The name of the property to get the value for.
     * @param[out] error Reference to a boolean value that will receve the error state in case something goes wrong.
     *
     * @return The value of the property. May be invalid if the error reference was set to <code>true</code>.
     */
    virtual variant_t get(const std::string &identifier, bool &error) = 0;

    /**
     * @brief execute Executes the named action with the supplied arguments.
     *
     * @param[in] name Name of the action to execute.
     * @param[in] args Arguments for the action's execution.
     *
     * @return <code>True</code> if executed correctly, <code>false</code> if not.
     */
    virtual bool execute(const std::string &name, const std::vector<variant_t> &args) = 0;
};

} // End namespace wf.

#endif // RULE_INTERFACE_HPP
