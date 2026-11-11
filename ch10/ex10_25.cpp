#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// 10.25: rewrite the biggies program using check_size and bind instead of
// a lambda that captures sz.

using std::placeholders::_1;

bool is_shorter(const std::string &lhs, const std::string &rhs)
{
    return lhs.size() < rhs.size();
}

bool check_size(const std::string &s, std::string::size_type sz)
{
    return s.size() >= sz;
}

void elim_dups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void print_long_words(const std::vector<std::string> &words,
                      std::vector<std::string>::const_iterator first,
                      std::string::size_type sz)
{
    std::cout << "10.25 " << (words.cend() - first) << " word(s) of length "
              << sz << " or longer:";
    for (auto it = first; it != words.cend(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void biggies(std::vector<std::string> words, std::string::size_type sz)
{
    elim_dups(words);
    std::stable_sort(words.begin(), words.end(), is_shorter);
    auto is_long_enough = std::bind(check_size, _1, sz);
    auto first = std::find_if(words.cbegin(), words.cend(), is_long_enough);
    print_long_words(words, first, sz);
}

int main()
{
    const std::vector<std::string> source{"the", "quick", "red", "fox", "jumps",
                                          "over", "the", "slow", "red", "turtle"};
    std::string::size_type sz = 0;
    if (!(std::cin >> sz))
    {
        std::cerr << "Expected a length.\n";
        return 1;
    }
    biggies(source, sz);
    return 0;
}
