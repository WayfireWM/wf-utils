#ifndef LITERAL_HPP
#define LITERAL_HPP

#include <string>
#include <variant>

class literal_t
{
public:
    enum class type_t
    {
        INT,
        CHAR,
        BOOL,
        FLOAT,
        DOUBLE,
        STRING,
    };

    using value_t = std::variant<int, char, bool, float, double, std::string>;

    literal_t(const std::string &s);

    std::string to_string() const;
    type_t type;
    value_t value;
};

#endif // LITERAL_HPP
