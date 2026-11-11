#include <iostream>
#include <string>

// 3.5: concatenate all input into one string, first without separators and
// then with a single space between words. An empty line ends the input.

int main()
{
    std::string joined, spaced, word;
    while (std::cin >> word)
    {
        if (word == "stop")
        {
            break;
        }
        joined += word;
        if (!spaced.empty())
        {
            spaced += ' ';
        }
        spaced += word;
    }
    std::cout << joined << '\n';
    std::cout << spaced << '\n';
    return 0;
}
