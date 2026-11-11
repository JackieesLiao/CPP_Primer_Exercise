#include <iostream>
#include <map>
#include <string>
#include <vector>

// 11.20: count words through insert's return value, which reports whether
// the key already existed and, if so, hands back the existing entry.
// 11.21: the same counting compressed into one statement per word.

std::map<std::string, std::size_t> count_with_branch(const std::vector<std::string> &words)
{
    std::map<std::string, std::size_t> counts;
    for (const std::string &word : words)
    {
        auto result = counts.insert({word, 1});
        if (!result.second)
        {
            ++result.first->second;
        }
    }
    return counts;
}

std::map<std::string, std::size_t> count_with_expression(const std::vector<std::string> &words)
{
    std::map<std::string, std::size_t> counts;
    for (const std::string &word : words)
    {
        ++(counts.insert({word, 0}).first->second);
    }
    return counts;
}

void print_counts(const char *label, const std::map<std::string, std::size_t> &counts)
{
    std::cout << label;
    for (const auto &entry : counts)
    {
        std::cout << " (" << entry.first << ", " << entry.second << ')';
    }
    std::cout << '\n';
}

int main()
{
    const std::vector<std::string> words{"hello", "world", "hello", "primer",
                                         "world", "hello"};
    print_counts("11.20:", count_with_branch(words));
    print_counts("11.21:", count_with_expression(words));
    return 0;
}
