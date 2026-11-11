#include <fstream>
#include <iostream>
#include <string>

#include "StrBlob.h"

// 12.20: read an input file line by line into a StrBlob and print every
// element through StrBlobPtr.
// 12.22: walk the same data with ConstStrBlobPtr over a const StrBlob.

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ex12_19_20_22 textfile\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }

    StrBlob lines;
    std::string line;
    while (std::getline(input, line))
    {
        lines.push_back(line);
    }

    std::cout << "through StrBlobPtr:\n";
    for (StrBlobPtr it = lines.begin(); it != lines.end(); it.increment())
    {
        std::cout << it.deref() << '\n';
    }

    const StrBlob &frozen = lines;
    std::cout << "through ConstStrBlobPtr:\n";
    for (ConstStrBlobPtr it = frozen.cbegin(); it != frozen.cend(); it.increment())
    {
        std::cout << it.deref() << '\n';
    }
    return 0;
}
