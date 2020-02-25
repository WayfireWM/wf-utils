#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <iterator>
#include <string>

namespace wf
{

template <typename T_CONTAINER, typename T_ITEM>
bool contains(const T_CONTAINER &container, const T_ITEM &item)
{
    auto begin = std::cbegin(container);
    auto end = std::cend(container);
    return std::find(begin, end, item) != end;
}

inline void ltrim(std::string &s)
{
    auto lambda = [] (int ch) { return !std::isspace(ch); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), lambda));
}

inline void rtrim(std::string &s)
{
    auto lambda = [] (int ch) { return !std::isspace(ch); };
    s.erase(std::find_if(s.rbegin(), s.rend(), lambda).base(), s.end());
}

inline void trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}

} // End namespace wf.

#endif // UTILS_HPP
