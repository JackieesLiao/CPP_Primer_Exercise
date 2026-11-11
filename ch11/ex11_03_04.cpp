#include <cctype>
#include <iostream>
#include <map>
#include <string>

// 11.3: count how often each word occurs with map<string, size_t>.
// 11.4: extend the count by lowercasing every word and stripping
// punctuation, so "Example." and "example" share one entry.

std::string normalize(const std::string &word)
{
    std::string cleaned;
    for (const char character : word)
    {
        if (!std::ispunct(static_cast<unsigned char>(character)))
        {
            cleaned += static_cast<char>(
                std::tolower(static_cast<unsigned char>(character)));
        }
    }
    return cleaned;
}

int main()
{
    std::map<std::string, std::size_t> counts;
    std::string word;
    while (std::cin >> word)
    {
        ++counts[normalize(word)];
    }
    for (const auto &entry : counts)
    {
        std::cout << entry.first << " occurs " << entry.second << " time(s)\n";
    }
    return 0;
}
