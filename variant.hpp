#ifndef VARIANT_HPP
#define VARIANT_HPP

#include <string>
#include <variant>

namespace wf
{

using variant_t = std::variant<int, char, bool, float, double, std::string>;

enum class variant_type_t
{
    INT,
    CHAR,
    BOOL,
    FLOAT,
    DOUBLE,
    STRING,
};

bool is_int(const variant_t &v);
bool is_char(const variant_t &v);
bool is_bool(const variant_t &v);
bool is_float(const variant_t &v);
bool is_double(const variant_t &v);
bool is_string(const variant_t &v);

variant_type_t type(const variant_t v);

int get_int(const variant_t &v);
char get_char(const variant_t &v);
bool get_bool(const variant_t &v);
float get_float(const variant_t &v);
double get_double(const variant_t &v);
std::string get_string(const variant_t &v);

std::string to_string(const variant_t &v);

} // End namespace wf.

#endif // VARIANT_HPP
