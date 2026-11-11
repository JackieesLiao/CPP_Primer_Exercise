#include <fstream>
#include <iostream>
#include <string>

#include "StrBlobTextQuery.h"

// 12.32: the text query program again, this time on top of StrBlob. The
// query interface and printed output match the 12.27 version.

void run_queries(std::ifstream &input)
{
    const StrBlobTextQuery document(input);
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
        std::cerr << "Usage: ex12_32 textfile\n";
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
