#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

// 10.33: read integers from an input file and write the even ones to the
// first output file and the odd ones to the second, using istream_iterator
// and ostream_iterator. Negative odd numbers also land in the odd file
// because only a remainder of 0 marks an even value.

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: ex10_33 inputfile evenfile oddfile\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }
    std::ofstream even_output(argv[2]);
    std::ofstream odd_output(argv[3]);
    if (!even_output || !odd_output)
    {
        std::cerr << "Cannot open the output files.\n";
        return 1;
    }

    std::istream_iterator<int> reader(input), eof;
    std::ostream_iterator<int> even_writer(even_output, " ");
    std::ostream_iterator<int> odd_writer(odd_output, " ");
    while (reader != eof)
    {
        if (*reader % 2 == 0)
        {
            *even_writer++ = *reader;
        }
        else
        {
            *odd_writer++ = *reader;
        }
        ++reader;
    }
    return 0;
}
