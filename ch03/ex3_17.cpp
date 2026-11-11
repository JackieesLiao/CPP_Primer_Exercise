#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// 3.17: read words into a vector, uppercase them, then print each one on
// its own line.

int main()
{
    std::vector<std::string> words;
    std::string word;
    while (std::cin >> word)
    {
        if (word == "stop")
        {
            break;
        }
        words.push_back(word);
    }
    for (std::string &entry : words)
    {
        for (char &character : entry)
        {
            character = static_cast<char>(std::toupper(static_cast<unsigned char>(character)));
        }
    }
    for (const std::string &entry : words)
    {
        std::cout << entry << '\n';
    }
    return 0;
}
