#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

// 11.7: a map from family name to the vector of children's names. The
// subscript operator creates an empty entry on first use, so a family with
// no children yet still shows up after add_family.
// 11.8: membership tests against excluded words go through a set, which
// organizes itself for fast lookup and avoids the duplicates a vector
// would need erased.

void add_family(std::map<std::string, std::vector<std::string>> &families,
                const std::string &family)
{
    families[family];
}

void add_child(std::map<std::string, std::vector<std::string>> &families,
               const std::string &family, const std::string &child)
{
    families[family].push_back(child);
}

int main()
{
    std::map<std::string, std::vector<std::string>> families;
    add_family(families, "Li");
    add_child(families, "Li", "Ming");
    add_child(families, "Li", "Xia");
    add_child(families, "Wang", "Lei");
    for (const auto &family : families)
    {
        std::cout << family.first << ':';
        for (const std::string &child : family.second)
        {
            std::cout << ' ' << child;
        }
        std::cout << '\n';
    }

    const std::set<std::string> excluded{"the", "but", "and"};
    const std::vector<std::string> input{"the", "quick", "and", "fox"};
    std::vector<std::string> kept;
    for (const std::string &word : input)
    {
        if (excluded.find(word) == excluded.cend())
        {
            kept.push_back(word);
        }
    }
    std::cout << "kept:";
    for (const std::string &word : kept)
    {
        std::cout << ' ' << word;
    }
    std::cout << '\n';
    return 0;
}
