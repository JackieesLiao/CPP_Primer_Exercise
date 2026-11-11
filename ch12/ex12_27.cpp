#include <fstream>
#include <iostream>
#include <string>

#include "TextQuery.h"

// 12.27: the text query program. Words typed on standard input are looked
// up until the input ends; 12.28 (no library containers), 12.29 (loop
// shape) and 12.31 (vector vs set) are discussed in the README.

void run_queries(std::ifstream &input)
{
    const TextQuery document(input);
    std::string word;
    std::cout << "words to look up: " << std::flush;
    while (std::cin >> word)
    {
        print(std::cout, document.query(word)) << '\n';
        std::cout << "words to look up: " << std::flush;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ex12_27 textfile\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }
    run_queries(input);
    return 0;
}
