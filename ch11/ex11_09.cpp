#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

// 11.9: map each word to the list of line numbers it appears on. The list
// appends in reading order; an empty line ends the input.

int main()
{
    std::map<std::string, std::list<int>> word_lines;
    std::string line;
    int line_number = 0;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            break;
        }
        ++line_number;
        std::istringstream stream(line);
        std::string word;
        while (stream >> word)
        {
            word_lines[word].push_back(line_number);
        }
    }
    for (const auto &entry : word_lines)
    {
        std::cout << entry.first << ":";
        for (const int number : entry.second)
        {
            std::cout << ' ' << number;
        }
        std::cout << '\n';
    }
    return 0;
}
