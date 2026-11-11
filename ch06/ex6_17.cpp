#include <cctype>
#include <iostream>
#include <string>

// 6.17: (a) report whether a string contains any uppercase letter; the
// string is only read, so it is passed as a const reference.
// (b) change every character to lowercase; the string is modified, so the
// parameter is a plain reference.

bool contains_uppercase(const std::string &text)
{
    for (const char character : text)
    {
        if (std::isupper(static_cast<unsigned char>(character)))
        {
            return true;
        }
    }
    return false;
}

void to_lowercase(std::string &text)
{
    for (char &character : text)
    {
        character = static_cast<char>(std::tolower(static_cast<unsigned char>(character)));
    }
}

int main()
{
    const std::string sample = "Hello, World!";
    std::string copy = sample;
    std::cout << "contains uppercase: " << contains_uppercase(sample) << '\n';
    to_lowercase(copy);
    std::cout << "lowercased: " << copy << '\n';
    return 0;
}
