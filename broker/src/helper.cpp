#include <helper.hpp>

namespace helper
{
    std::vector<std::string> tokenize(const std::string &s, const std::string &del)
    {
        std::vector<std::string> res;
        int start = 0;
        int end = s.find(del);
        while (end != -1)
        {
            res.push_back(s.substr(start, end - start));
            start = end + del.size();
            end = s.find(del, start);
        }
        res.push_back(s.substr(start, end - start));
        return res;
    }

    std::unordered_map<std::string, std::string> fetch_params(const std::string_view &query)
    {
        auto replaceAll = [](std::string &source, const std::string &from, const std::string &to)
        {
            std::string newString;
            newString.reserve(source.length());

            std::string::size_type lastPos = 0;
            std::string::size_type findPos;

            while (std::string::npos != (findPos = source.find(from, lastPos)))
            {
                newString.append(source, lastPos, findPos - lastPos);
                newString += to;
                lastPos = findPos + from.length();
            }

            newString += source.substr(lastPos);
            source.swap(newString);
        };

        std::unordered_map<std::string, std::string> query_map;
        int i, index = 0;
        std::string key, value;
        for (i = 0; i < query.length(); i++)
        {
            if (query[i] == '=')
            {
                key = query.substr(index, i - index);
                index = i + 1;
            }
            else if (query[i] == '&')
            {
                value = query.substr(index, i - index);
                replaceAll(value, "%20", " ");
                replaceAll(value, "%22", "");
                index = i + 1;
                query_map[key] = value;
            }
        }

        value = query.substr(index, i - index);
        replaceAll(value, "%20", " ");
        replaceAll(value, "%22", "");
        index = i + 1;
        query_map[key] = value;

        return query_map;
    }

}; // namespace helper
