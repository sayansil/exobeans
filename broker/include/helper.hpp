#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace helper
{
    extern std::unordered_map<std::string, std::string> fetch_params(const std::string_view &query);
    extern std::vector<std::string> tokenize(const std::string &s, const std::string &del = " ");
};

#endif // HELPER_HPP