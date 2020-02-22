#ifndef CONDITION_HPP
#define CONDITION_HPP

#include <string>

class rule_interface_t;

class condition_t
{
public:
    condition_t();
    virtual ~condition_t();

    virtual bool evaluate(rule_interface_t &interface, bool &error) = 0;

    virtual std::string to_string() const = 0;
};

#endif // CONDITION_HPP
