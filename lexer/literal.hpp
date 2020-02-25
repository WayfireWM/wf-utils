#ifndef LITERAL_HPP
#define LITERAL_HPP

#include "variant.hpp"
#include <string>

namespace wf
{

variant_t parse_literal(const std::string &s);

} // End namespace wf.

#endif // LITERAL_HPP
