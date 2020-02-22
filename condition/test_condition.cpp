#include "test_condition.hpp"
#include "rule/rule_interface.hpp"
#include "variant.hpp"
#include <string>
#include <variant>

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
    out.append(::to_string(_value));
    return out;
}
