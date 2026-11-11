#include <cctype>
#include <iostream>
#include <string>

// 3.6: convert every character of the input string to uppercase with a
// range-for that uses a reference so it can modify the string.

int main()
{
    std::string text;
    if (!(std::cin >> text))
    {
        std::cerr << "Expected a string.\n";
        return 1;
    }
    for (char &character : text)
    {
        character = static_cast<char>(std::toupper(static_cast<unsigned char>(character)));
    }
    std::cout << text << '\n';
    return 0;
}
