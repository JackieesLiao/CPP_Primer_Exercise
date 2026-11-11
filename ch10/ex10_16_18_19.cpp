#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Three versions of the book's biggies program:
// 10.16 locates the first long word with find_if and a lambda,
// 10.18 replaces find_if with partition,
// 10.19 replaces partition with stable_partition to keep the relative
// order of the short words intact.

bool is_shorter(const std::string &lhs, const std::string &rhs)
{
    return lhs.size() < rhs.size();
}

void elim_dups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void print_long_words(const char *label,
                      std::vector<std::string>::const_iterator first_long,
                      std::vector<std::string>::const_iterator last_long,
                      std::string::size_type sz)
{
    std::cout << label << ' ' << (last_long - first_long) << " word(s) of length "
              << sz << " or longer:";
    for (auto it = first_long; it != last_long; ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void biggies_find_if(std::vector<std::string> words, std::string::size_type sz)
{
    elim_dups(words);
    std::stable_sort(words.begin(), words.end(), is_shorter);
    auto is_long_enough = [sz](const std::string &word)
    {
        return word.size() >= sz;
    };
    auto first = std::find_if(words.cbegin(), words.cend(), is_long_enough);
    print_long_words("10.16 find_if:", first, words.cend(), sz);
}

void biggies_partition(std::vector<std::string> words, std::string::size_type sz)
{
    elim_dups(words);
    std::stable_sort(words.begin(), words.end(), is_shorter);
    auto is_long_enough = [sz](const std::string &word)
    {
        return word.size() >= sz;
    };
    auto first = std::partition(words.begin(), words.end(), is_long_enough);
    print_long_words("10.18 partition:", words.cbegin(), first, sz);
}

void biggies_stable_partition(std::vector<std::string> words,
                              std::string::size_type sz)
{
    elim_dups(words);
    std::stable_sort(words.begin(), words.end(), is_shorter);
    auto is_long_enough = [sz](const std::string &word)
    {
        return word.size() >= sz;
    };
    auto first = std::stable_partition(words.begin(), words.end(), is_long_enough);
    print_long_words("10.19 stable_partition:", words.cbegin(), first, sz);
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
    biggies_find_if(source, sz);
    biggies_partition(source, sz);
    biggies_stable_partition(source, sz);
    return 0;
}
