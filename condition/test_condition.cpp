#include "test_condition.hpp"

#include <string>

#include "condition.hpp"
#include "variant.hpp"

#include "rule/rule_interface.hpp"

test_condition_t::test_condition_t(const std::string &identifier, const variant_t &value) : _identifier(identifier), _value(value)
{
}

test_condition_t::~test_condition_t()
{
}

equals_condition_t::equals_condition_t(const std::string &identifier, const variant_t &value) : test_condition_t(identifier, value)
{
}

equals_condition_t::~equals_condition_t()
{
}

bool equals_condition_t::evaluate(rule_interface_t &interface, bool &error)
{
    if (error)
    {
        return false;
    }

    auto value = interface.get(_identifier, error);

    if (error)
    {
        return false;
    }

    return value == _value;
}

std::string equals_condition_t::to_string() const
{
    std::string out = _identifier;
    out.append(" equals ");
    if (std::holds_alternative<int>(_value))
    {
        out.append(std::to_string(get_int(_value)));
    }
    else if (std::holds_alternative<std::string>(_value))
    {
        out.append(get_string(_value));
    }
    else
    {
        out.append("*VALUE*");
    }
    // TODO: Complete me.
    return out;
}
