#include <iostream>
#include <string>

// 3.4: compare two strings for equality and by dictionary order, then
// compare their lengths.

int main()
{
    std::string first, second;
    if (!(std::cin >> first >> second))
    {
        std::cerr << "Expected two strings.\n";
        return 1;
    }
    if (first == second)
    {
        std::cout << "equal\n";
    }
    else if (first > second)
    {
        std::cout << first << " is larger\n";
    }
    else
    {
        std::cout << second << " is larger\n";
    }
    if (first.size() == second.size())
    {
        std::cout << "same length\n";
    }
    else if (first.size() > second.size())
    {
        std::cout << first << " is longer\n";
    }
    else
    {
        std::cout << second << " is longer\n";
    }
    return 0;
}
