#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 10.9: read words, sort them, remove duplicates with unique + erase.

void print_words(const char *label, const std::vector<std::string> &words)
{
    std::cout << label;
    for (const std::string &word : words)
    {
        std::cout << ' ' << word;
    }
    std::cout << '\n';
}

int main()
{
    std::vector<std::string> words;
    std::string word;
    while (std::cin >> word)
    {
        words.push_back(word);
    }
    print_words("as read:", words);

    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
    print_words("after sort, unique and erase:", words);
    return 0;
}
