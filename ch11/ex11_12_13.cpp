#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

// 11.12: read string and int sequences from standard input and store each
// pair in a vector.
// 11.13: the same pair can be inserted three ways: brace initialization,
// make_pair and emplace_back. The map at the end shows that a pair is a
// value_type of map<string, string> as well; the words here are first and
// last names of the sample input "Ann Lee Bob Wu Cai Xu".

int main()
{
    std::vector<std::pair<std::string, int>> ages;
    std::string name;
    int age = 0;
    while (std::cin >> name >> age)
    {
        ages.push_back({name, age});
    }
    for (const auto &entry : ages)
    {
        std::cout << entry.first << " is " << entry.second << '\n';
    }

    std::vector<std::pair<std::string, std::string>> names;
    names.push_back({"Ann", "Lee"});
    names.push_back(std::make_pair("Bob", "Wu"));
    names.emplace_back("Cai", "Xu");
    for (const auto &entry : names)
    {
        std::cout << entry.first << ' ' << entry.second << '\n';
    }

    std::map<std::string, std::string> by_first_name;
    for (const auto &entry : names)
    {
        by_first_name.insert(entry);
    }
    for (const auto &entry : by_first_name)
    {
        std::cout << entry.first << " -> " << entry.second << '\n';
    }
    return 0;
}
