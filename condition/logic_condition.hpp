#ifndef LOGIC_CONDITION_HPP
#define LOGIC_CONDITION_HPP

#include "condition.hpp"
#include <memory>
#include <string>

class rule_interface_t;

class or_condition_t : public condition_t
{
public:
    or_condition_t();
    virtual ~or_condition_t() override;

    virtual bool evaluate(rule_interface_t &interface, bool &error) override;

    virtual std::string to_string() const override;

    std::shared_ptr<condition_t> left;
    std::shared_ptr<condition_t> right;
};

class and_condition_t : public condition_t
{
public:
    and_condition_t();
    virtual ~and_condition_t() override;

    virtual bool evaluate(rule_interface_t &interface, bool &error) override;

    virtual std::string to_string() const override;

    std::shared_ptr<condition_t> left;
    std::shared_ptr<condition_t> right;
};

class not_condition_t : public condition_t
{
public:
    not_condition_t();
    virtual ~not_condition_t() override;

    virtual bool evaluate(rule_interface_t &interface, bool &error) override;

    virtual std::string to_string() const override;

    std::shared_ptr<condition_t> child;
};

#endif // LOGIC_CONDITION_HPP
