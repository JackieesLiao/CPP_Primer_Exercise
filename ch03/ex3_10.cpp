#include <cctype>
#include <iostream>
#include <string>

// 3.10: remove the punctuation characters from the input string.

int main()
{
    std::string text, cleaned;
    if (!(std::cin >> text))
    {
        std::cerr << "Expected a string.\n";
        return 1;
    }
    for (const char character : text)
    {
        if (!std::ispunct(static_cast<unsigned char>(character)))
        {
            cleaned += character;
        }
    }
    std::cout << cleaned << '\n';
    return 0;
}
