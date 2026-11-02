#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

int main()
{
    const std::list<const char *> source{"alpha", "beta"};
    std::vector<std::string> words;
    words.assign(source.begin(), source.end());
    for (const std::string &word : words)
    {
        std::cout << word << '\n';
    }

    const std::vector<int> first{1, 2, 3};
    const std::vector<int> second{1, 2, 3};
    const std::list<int> third{1, 2, 3};
    const bool same_vectors = first == second;
    const bool same_list =
        first.size() == third.size() && std::equal(first.begin(), first.end(), third.begin());
    std::cout << std::boolalpha << same_vectors << ' ' << same_list << '\n';
    return 0;
}
