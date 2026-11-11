#include <iostream>
#include <string>

// 5.19: a do while loop that asks for two strings and prints the shorter
// one, repeating until the input runs out.

int main()
{
    std::string first, second;
    do
    {
        std::cout << "two strings (empty input ends): " << std::flush;
        if (!(std::cin >> first >> second))
        {
            break;
        }
        if (first.size() <= second.size())
        {
            std::cout << first << '\n';
        }
        else
        {
            std::cout << second << '\n';
        }
    } while (true);
    return 0;
}
