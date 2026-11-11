#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 10.11: sort the deduplicated words by length while keeping the
// alphabetical order of words with equal length.

bool is_shorter(const std::string &lhs, const std::string &rhs)
{
    return lhs.size() < rhs.size();
}

void print_words(const char *label, const std::vector<std::string> &words)
{
    std::cout << label;
    for (const std::string &word : words)
    {
        std::cout << ' ' << word;
    }
    std::cout << '\n';
}

void elim_dups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

int main()
{
    std::vector<std::string> words;
    std::string word;
    while (std::cin >> word)
    {
        words.push_back(word);
    }

    elim_dups(words);
    print_words("after elim_dups:", words);

    std::stable_sort(words.begin(), words.end(), is_shorter);
    print_words("after stable_sort by length:", words);
    return 0;
}
