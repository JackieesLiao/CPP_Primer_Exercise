#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// 10.22: count the words longer than 6 letters with check_size and bind.
// 10.23 is discussed in the README; 10.24 finds the first int that is greater
// than the length of a given string. The int arrives through the placeholder,
// so the helper below puts the size parameter first; otherwise the placeholder
// would have to convert an int into a string.

using std::placeholders::_1;

bool check_size(const std::string &s, std::string::size_type sz)
{
    return s.size() >= sz;
}

bool value_exceeds(std::string::size_type sz, const std::string &s)
{
    return s.size() < sz;
}

int main()
{
    const std::vector<std::string> words{"stl", "algorithm", "iterator",
                                         "predicate", "sort", "stable_partition"};
    auto longer_than_six = std::bind(check_size, _1, 6);
    std::cout << "10.22 words of length 6 or more: "
              << std::count_if(words.cbegin(), words.cend(), longer_than_six)
              << '\n';

    const std::string word = "turtle";
    const std::vector<int> values{1, 2, 3, 4, 5, 6, 7, 8};
    auto greater_than_word = std::bind(value_exceeds, _1, word);
    auto found = std::find_if(values.cbegin(), values.cend(), greater_than_word);
    if (found == values.cend())
    {
        std::cout << "10.24 no value exceeds " << word.size() << '\n';
    }
    else
    {
        std::cout << "10.24 the first value above " << word.size()
                  << " is " << *found << '\n';
    }
    return 0;
}
