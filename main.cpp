#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <streambuf>
#include <string>

#include "utils.hpp"

#include "lexer/lexer.hpp"
#include "parser/rule_parser.hpp"
#include "rule/rule.hpp"
#include "rule/rule_interface.hpp"

class test_t
{
public:
    void maximize()
    {
        std::cout << "void maximize()" << std::endl;
    }

    void minimize()
    {
        std::cout << "void minimize()" << std::endl;
    }

    int property_a;

    double get_property_b() const
    {
        std::cout << "double get_property_b()" << std::endl;
        return _property_b;
    }

    void set_property_b(double property_b)
    {
        std::cout << "void set_property_b(" << property_b << ")" << std::endl;
        _property_b = property_b;
    }
private:
    double _property_b;
};

class test_interface_t : public rule_interface_t
{
public:
    test_interface_t(std::shared_ptr<test_t> test) : _test(test)
    {
    }

    virtual ~test_interface_t() override;

    virtual symbol_t::value_t get(const std::string &identifier, bool &error) override
    {
        error = false;
        if (_test != nullptr)
        {
            if (identifier == "property_a")
            {
                return _test->property_a;
            }
            else if (identifier == "property_b")
            {
                return _test->get_property_b();
            }
        }

        error = true;
        return symbol_t::value_t();
    }

    virtual bool set(const std::string &identifier, const symbol_t::value_t &value) override
    {
        auto error = true;
        if (_test != nullptr)
        {
            if (identifier == "property_a")
            {
                _test->property_a = std::get<decltype (_test->property_a)>(value);
                error = false;
            }
            else if (identifier == "property_b")
            {
                _test->set_property_b(std::get<decltype (_test->get_property_b())>(value));
            }
        }

        return error;
    }

    virtual bool maximize() override
    {
        if (_test != nullptr)
        {
            _test->maximize();
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual bool minimize() override
    {
        if (_test != nullptr)
        {
            _test->minimize();
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    std::shared_ptr<test_t> _test;
};

test_interface_t::~test_interface_t()
{
}

int main()
{
    std::string text_reverse = "one two three four five";

    auto data = std::make_shared<test_t>();
    data->property_a = 5;
    data->set_property_b(0.5);

    test_interface_t data_interface(data);

    std::set<std::string> text = {
        "on created if moo then set property_b 0.8",
        "on created if moo then set property_a 8",
        "on created if moo then maximize",
        "on created if moo then minimize",
    };

    lexer_t lexer;
    rule_parser_t rule_parser;

    std::vector<std::shared_ptr<rule_t>> rules;

    for (const auto &t : text)
    {
        lexer.reset(t);
        rules.push_back(rule_parser.parse(lexer));
    }

    for (auto rule : rules)
    {
        rule->apply("created", data_interface);
    }

    lexer.reset(text_reverse);

    auto s = lexer.parse_symbol();
    auto p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    lexer.reverse();
    p = lexer.current_symbol_position();
    std::cout << "reversed to p: " << p << std::endl;

    s = lexer.parse_symbol();
    p = lexer.current_symbol_position();
    std::cout << "p: " << p << " s: " << s.to_string() << std::endl;

    return 0;
}
