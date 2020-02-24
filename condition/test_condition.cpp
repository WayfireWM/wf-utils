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

true_condition_t::true_condition_t() : test_condition_t("", 0)
{
}

true_condition_t::~true_condition_t()
{
}

bool true_condition_t::evaluate(rule_interface_t &interface, bool &error)
{
    static_cast<void>(interface);

    if (error)
    {
        return false;
    }

    return true;
}

std::string true_condition_t::to_string() const
{
    return "true";
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

contains_condition_t::contains_condition_t(const std::string &identifier, const variant_t &value) : test_condition_t(identifier, value)
{
}

contains_condition_t::~contains_condition_t()
{
}

bool contains_condition_t::evaluate(rule_interface_t &interface, bool &error)
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

    // If the retrieved value or search value is not a string, this can't work.
    if ((!is_string(_value)) || (!is_string(value)))
    {
        error = true;
        return false;
    }

    return get_string(_value).find(get_string(value)) != std::string::npos;
}

std::string contains_condition_t::to_string() const
{
    std::string out = _identifier;
    out.append(" contains ");
    out.append(::to_string(_value));
    return out;
}
