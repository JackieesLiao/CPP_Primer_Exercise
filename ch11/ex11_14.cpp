#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

// 11.14: extend the family map so every child carries a birthday. The
// mapped value is a vector of pairs; emplace_back constructs the pair in
// place from the two strings.

int main()
{
    std::map<std::string, std::vector<std::pair<std::string, std::string>>>
        families;
    families["Li"].emplace_back("Ming", "1990-01-01");
    families["Li"].emplace_back("Xia", "1993-05-20");
    families["Wang"].emplace_back("Lei", "1988-11-30");
    for (const auto &family : families)
    {
        std::cout << family.first << ':';
        for (const auto &child : family.second)
        {
            std::cout << ' ' << child.first << " (" << child.second << ')';
        }
        std::cout << '\n';
    }
    return 0;
}
