#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ex9_49 WORD_FILE\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open word file.\n";
        return 1;
    }

    // Restrict this exercise to lowercase ASCII words.
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string ascenders_and_descenders = "bdfghijklpqty";
    std::string word;
    std::string longest;
    while (input >> word)
    {
        if (word.find_first_not_of(lowercase) != std::string::npos)
        {
            continue;
        }
        if (word.find_first_of(ascenders_and_descenders) == std::string::npos &&
            word.size() > longest.size())
        {
            longest = word;
        }
    }
    if (input.bad())
    {
        std::cerr << "Error reading word file.\n";
        return 1;
    }
    std::cout << longest << '\n';
    return 0;
}
