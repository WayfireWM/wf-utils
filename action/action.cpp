#include "action.hpp"
#include "rule/rule_interface.hpp"

namespace wf
{

action_t::action_t(const std::string &name, const std::vector<variant_t> &args) : _name(name), _args(args)
{
}

bool action_t::execute(rule_interface_t &interface)
{
    return interface.execute(_name, _args);
}

} // End namespace wf.
