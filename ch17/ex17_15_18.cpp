#include <iostream>
#include <regex>
#include <string>
#include <vector>

// 17.15/17.16/17.18: the i-before-e rule. The pattern "[^c]ei" (17.15)
// flags words where ei does not follow c; 17.16 asks how "[^c]ei" differs
// from "[^c]e[^i]" style variants; 17.18 scans a whole text with
// sregex_iterator and lists every violating word.

bool check_rule(const std::string &word)
{
    static const std::regex pattern("[^c]ei");
    return !std::regex_search(word, pattern);
}

int main()
{
    const std::vector<std::string> words{"friend", "freind", "achieve",
                                         "receipt", "neighbor", "freight"};
    for (const std::string &word : words)
    {
        // The naive pattern also flags correctly spelled words such as
        // neighbor and freight, because their "ei" sounds like "ay";
        // that limitation is exactly what 17.16 discusses.
        std::cout << word << " flagged by [^c]ei: " << std::boolalpha
                  << !check_rule(word) << '\n';
    }

    const std::string text("freind achieve recieve neighbor theif freight");
    static const std::regex violating("[[:alpha:]]*[^c]ei[[:alpha:]]*");
    std::cout << "violating words:";
    for (std::sregex_iterator it(text.cbegin(), text.cend(), violating), end_it;
         it != end_it; ++it)
    {
        std::cout << ' ' << it->str();
    }
    std::cout << '\n';
    return 0;
}
