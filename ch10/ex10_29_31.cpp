#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// 10.29: read the words of a file into a vector with istream_iterator.
// 10.30: read integers from standard input, sort them and print with
//        ostream_iterator.
// 10.31: repeat the printing with unique_copy.

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ex10_29_31 wordfile\n"
                     "Integers are then read from standard input.\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }

    std::istream_iterator<std::string> word_reader(input), word_eof;
    std::vector<std::string> words(word_reader, word_eof);
    std::cout << "10.29 words from file:";
    for (const std::string &word : words)
    {
        std::cout << ' ' << word;
    }
    std::cout << '\n';

    std::istream_iterator<int> number_reader(std::cin), number_eof;
    std::vector<int> numbers(number_reader, number_eof);
    std::sort(numbers.begin(), numbers.end());

    std::ostream_iterator<int> out(std::cout, " ");
    std::cout << "10.30 sorted integers:";
    std::copy(numbers.cbegin(), numbers.cend(), out);
    std::cout << '\n';

    std::ostream_iterator<int> unique_out(std::cout, " ");
    std::cout << "10.31 unique integers:";
    std::unique_copy(numbers.cbegin(), numbers.cend(), unique_out);
    std::cout << '\n';
    return 0;
}
