#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ex8_10 FILE\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open input\n";
        return 1;
    }
    std::vector<std::string> lines;
    std::string line, word;
    while (std::getline(input, line))
    {
        lines.push_back(line);
    }
    if (input.bad())
    {
        return 1;
    }
    for (const auto &text : lines)
    {
        std::istringstream record(text);
        while (record >> word)
        {
            std::cout << word << '\n';
        }
    }
}
