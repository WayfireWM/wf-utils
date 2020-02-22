#ifndef ACTION_HPP
#define ACTION_HPP

#include "variant.hpp"
#include <string>
#include <vector>

class rule_interface_t;

class action_t
{
public:
    action_t(const std::string &name, const std::vector<variant_t> &args);

    /**
     * @brief execute
     * @param interface
     * @return <code>True</code> if an error occurred, <code>false</code> if not.
     */
    bool execute(rule_interface_t &interface);
private:
    std::string _name;
    std::vector<variant_t> _args;
};

#endif // ACTION_HPP
