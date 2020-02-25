#ifndef LOGIC_CONDITION_HPP
#define LOGIC_CONDITION_HPP

#include "condition.hpp"
#include <memory>
#include <string>

namespace wf
{

class rule_interface_t;

/**
 * @brief The or_condition_t class is a logical OR condition. It bundles 2 conditions and evaluates them in an
 *        OR relationship.
 */
class or_condition_t : public condition_t
{
public:
    /**
     * @brief or_condition_t Constructor.
     */
    or_condition_t();

    /**
     * @copydoc wf::~condition_t()
     */
    virtual ~or_condition_t() override;

    /**
     * @copydoc wf::evaluate()
     */
    virtual bool evaluate(rule_interface_t &interface, bool &error) override;

    /**
     * @copydoc wf::to_string()
     */
    virtual std::string to_string() const override;

    /**
     * @brief left is the left operand of the OR operation.
     */
    std::shared_ptr<condition_t> left;

    /**
     * @brief right is the right operatnd of the OR operation.
     */
    std::shared_ptr<condition_t> right;
};

/**
 * @brief The and_condition_t class is a logical AND condition. It bundles 2 conditions and evaluates them in an
 *        AND relationship.
 */
class and_condition_t : public condition_t
{
public:
    /**
     * @brief and_condition_t Constructor.
     */
    and_condition_t();

    /**
     * @copydoc wf::~condition_t()
     */
    virtual ~and_condition_t() override;

    /**
     * @copydoc wf::evaluate()
     */
    virtual bool evaluate(rule_interface_t &interface, bool &error) override;

    /**
     * @copydoc wf::to_string()
     */
    virtual std::string to_string() const override;

    /**
     * @brief left is the left operand of the AND operation.
     */
    std::shared_ptr<condition_t> left;

    /**
     * @brief right is the right operand of the AND operation.
     */
    std::shared_ptr<condition_t> right;
};

/**
 * @brief The not_condition_t class is a logical NOT condition. It inverts the evaluated result of the child condition.
 */
class not_condition_t : public condition_t
{
public:
    /**
     * @brief not_condition_t Constructor.
     */
    not_condition_t();

    /**
     * @copydoc wf::~condition_t()
     */
    virtual ~not_condition_t() override;

    /**
     * @copydoc wf::evaluate()
     */
    virtual bool evaluate(rule_interface_t &interface, bool &error) override;

    /**
     * @copydoc wf::to_string()
     */
    virtual std::string to_string() const override;

    /**
     * @brief child is the child condition that will be inverted in evaluate().
     */
    std::shared_ptr<condition_t> child;
};

} // End namespace wf.

#endif // LOGIC_CONDITION_HPP
