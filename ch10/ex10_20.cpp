#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 10.20: count the words longer than 6 letters with count_if and a lambda.

int count_long_words(const std::vector<std::string> &words,
                     std::vector<std::string>::size_type sz)
{
    auto is_long = [sz](const std::string &word)
    {
        return word.size() > sz;
    };
    return static_cast<int>(std::count_if(words.cbegin(), words.cend(), is_long));
}

int main()
{
    const std::vector<std::string> words{"stl", "algorithm", "iterator",
                                         "predicate", "sort", "stable_partition"};
    std::cout << "words longer than 6 letters: "
              << count_long_words(words, 6) << '\n';
    return 0;
}
