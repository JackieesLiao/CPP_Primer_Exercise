#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ex8_05 FILE\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }
    std::vector<std::string> words;
    std::string word;
    while (input >> word)
    {
        words.push_back(word);
    }
    if (input.bad())
    {
        std::cerr << "Error reading input file\n";
        return 1;
    }
    for (const auto &w : words)
    {
        std::cout << w << '\n';
    }
}
