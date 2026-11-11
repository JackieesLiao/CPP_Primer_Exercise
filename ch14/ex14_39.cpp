#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 14.39: word counts with function objects: one counts the words longer
// than 5 letters, the other counts the words of length 1.

class LongerThan
{
public:
    explicit LongerThan(std::string::size_type limit) : bound(limit)
    {
    }

    bool operator()(const std::string &word) const
    {
        return word.size() > bound;
    }

private:
    std::string::size_type bound;
};

class EqualToLength
{
public:
    explicit EqualToLength(std::string::size_type limit) : bound(limit)
    {
    }

    bool operator()(const std::string &word) const
    {
        return word.size() == bound;
    }

private:
    std::string::size_type bound;
};

int main()
{
    std::vector<std::string> words;
    std::string word;
    while (std::cin >> word)
    {
        words.push_back(word);
    }
    std::cout << "longer than 5: "
              << std::count_if(words.begin(), words.end(), LongerThan(5))
              << '\n';
    std::cout << "exactly 1: "
              << std::count_if(words.begin(), words.end(), EqualToLength(1))
              << '\n';
    return 0;
}
