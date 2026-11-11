#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

// 11.16: an iterator of a map may change the mapped value but never the
// key, which is const.
// 11.17: copying between a set and a vector works with insert iterators in
// both directions; push_back/back_inserter is not available on a set.

int main()
{
    std::map<std::string, int> ages{{"Ann", 30}, {"Bob", 25}};
    auto map_it = ages.begin();
    map_it->second = 31;
    std::cout << "11.16 " << map_it->first << " is now " << map_it->second << '\n';

    const std::vector<int> numbers{2, 4, 6};
    std::set<int> number_set;
    std::copy(numbers.cbegin(), numbers.cend(),
              std::inserter(number_set, number_set.end()));
    std::vector<int> copied;
    std::copy(number_set.cbegin(), number_set.cend(), std::back_inserter(copied));
    std::cout << "11.17 from vector to set and back:";
    for (const int value : copied)
    {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
    return 0;
}
