#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> read_lines(const std::string &path)
{
    std::ifstream input(path);
    if (!input)
    {
        throw std::runtime_error("Cannot open input file");
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line))
    {
        lines.push_back(line);
    }
    if (input.bad())
    {
        throw std::runtime_error("Error reading input file");
    }
    return lines;
}
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ex8_04 FILE\n";
        return 1;
    }
    try
    {
        for (const auto &line : read_lines(argv[1]))
        {
            std::cout << line << '\n';
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
