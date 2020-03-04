#include "wayfire/lexer/lexer.hpp"
#include "wayfire/parser/rule_parser.hpp"
#include "wayfire/rule/rule.hpp"
#include "wayfire/rule/rule_interface.hpp"
#include "wayfire/variant.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

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

    std::string title;
private:
    double _property_b;
};

class test_interface_t : public wf::rule_interface_t
{
public:
    test_interface_t(std::shared_ptr<test_t> test) : _test(test)
    {
    }

    virtual ~test_interface_t() override;

    virtual wf::variant_t get(const std::string &identifier, bool &error) override
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
            else if (identifier == "title")
            {
                return _test->title;
            }
        }

        error = true;
        return wf::variant_t("");
    }

    virtual bool execute(const std::string &name, const std::vector<wf::variant_t> &args) override
    {
        auto error = _test == nullptr;
        if (!error)
        {
            if ((name == "set") && (args.size() == 2))
            {
                auto property = wf::get_string(args.at(0));
                if (property == "property_a")
                {
                    _test->property_a = wf::get_int(args.at(1));
                }
                else if (property == "property_b")
                {
                    _test->set_property_b(wf::get_double(args.at(1)));
                }
                else
                {
                    error = true;
                }
            }
            else if (name == "maximize")
            {
                _test->maximize();
            }
            else if (name == "minimize")
            {
                _test->minimize();
            }
            else
            {
                error = true;
            }
        }
        return error;
    }
private:
    std::shared_ptr<test_t> _test;
};

test_interface_t::~test_interface_t()
{
}

int main()
{
    /*
    lexer_t lexer("(a equals 3 | a equals 2) & (! x equals 4)");
    condition_parser_t parser;

    try
    {
        auto condition = parser.parse(lexer);
    }
    catch (std::runtime_error &e)
    {
        std::cout << "Malformed input:" << std::endl;
        std::cout << lexer.text() << std::endl;
        std::string pad;
        auto pos = lexer.current_symbol_position();
        for (std::size_t i = 0; i < pos; ++i)
        {
            pad.append(" ");
        }
        pad.append("^ ");
        std::cout << pad << e.what() << std::endl;

    }
    */



    std::string text_reverse = "one two three four five";

    auto data = std::make_shared<test_t>();
    data->property_a = 4;
    data->title = "Alacritty";

    test_interface_t data_interface(data);

    std::vector<std::string> text = {
        "on created if property_a equals 4 then set property_b 0.4",
        "on created if (property_a equals 4) | (property_a equals 8) then maximize else minimize",
        "on created then minimize",
        "on created then maximize else minimize",
        "on created if title contains \"   Alacritty   \" then maximize"
    };

    wf::lexer_t lexer;
    wf::rule_parser_t rule_parser;

    std::vector<std::shared_ptr<wf::rule_t>> rules;

    for (const auto &t : text)
    {
        lexer.reset(t);
        rules.push_back(rule_parser.parse(lexer));
    }

    for (auto rule : rules)
    {
        rule->apply("created", data_interface);
    }
    /*

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
*/
    return 0;
}
