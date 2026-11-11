#include <iostream>
#include <string>

// 3.2: first read a line at a time, then read one word per line.

int main()
{
    std::string line;
    std::cout << "lines:" << '\n';
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            break;
        }
        std::cout << line << '\n';
    }
    std::cout << "words:" << '\n';
    std::string word;
    while (std::cin >> word)
    {
        if (word == "stop")
        {
            break;
        }
        std::cout << word << '\n';
    }
    return 0;
}
