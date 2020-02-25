#ifndef RULE_INTERFACE_HPP
#define RULE_INTERFACE_HPP

#include "variant.hpp"
#include <string>
#include <vector>

namespace wf
{

class rule_interface_t
{
public:
    virtual ~rule_interface_t();
    virtual variant_t get(const std::string &identifier, bool &error) = 0;
    virtual bool execute(const std::string &name, const std::vector<variant_t> &args) = 0;
};

} // End namespace wf.

#endif // RULE_INTERFACE_HPP
