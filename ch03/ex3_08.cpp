#include <cctype>
#include <iostream>
#include <string>

// 3.8: uppercase with a classic for and a while over subscripts, both
// walking through the string without a reference.

int main()
{
    std::string text;
    if (!(std::cin >> text))
    {
        std::cerr << "Expected a string.\n";
        return 1;
    }
    for (std::string::size_type index = 0; index != text.size(); ++index)
    {
        text[index] = static_cast<char>(
            std::toupper(static_cast<unsigned char>(text[index])));
    }
    std::cout << text << '\n';

    std::string::size_type position = 0;
    while (position != text.size())
    {
        text[position] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(text[position])));
        ++position;
    }
    std::cout << text << '\n';
    return 0;
}
