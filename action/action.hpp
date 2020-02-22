#ifndef ACTION_HPP
#define ACTION_HPP

#include <string>
#include <vector>

#include "lexer/symbol.hpp"
#include "rule/rule_interface.hpp"

class action_t
{
public:
    action_t(const std::string &name, const std::vector<symbol_t::value_t> &args);

    /**
     * @brief execute
     * @param interface
     * @return <code>True</code> if an error occurred, <code>false</code> if not.
     */
    bool execute(rule_interface_t &interface);
private:
    std::string _name;
    std::vector<symbol_t::value_t> _args;
};

#endif // ACTION_HPP
