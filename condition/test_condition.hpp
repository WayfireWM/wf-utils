#ifndef TEST_CONDITION_HPP
#define TEST_CONDITION_HPP

#include <string>

#include "condition.hpp"
#include "variant.hpp"

#include "rule/rule_interface.hpp"

class test_condition_t : public condition_t
{
public:
    test_condition_t(const std::string &identifier, const variant_t &value);
    virtual ~test_condition_t() override;

    virtual bool evaluate(rule_interface_t &interface, bool &error) override = 0;

    virtual std::string to_string() const override = 0;
protected:
    std::string _identifier;
    variant_t _value;
};

class equals_condition_t : public test_condition_t
{
public:
    equals_condition_t(const std::string &identifier, const variant_t &value);
    virtual ~equals_condition_t() override;

    virtual bool evaluate(rule_interface_t &interface, bool &error) override;

    virtual std::string to_string() const override;
};

#endif // TEST_CONDITION_HPP
