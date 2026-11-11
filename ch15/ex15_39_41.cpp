#include <fstream>
#include <iostream>
#include <string>

#include "Query.h"

// 15.31/15.34/15.36/15.39/15.41: run word, negation, or, and and combined
// queries against the story file. Each result prints the rep() of the
// expression tree before the matched lines.

void run_query(const char *label, const Query &query, const TextQuery &file)
{
    std::cout << "--- " << label << ": " << query.rep() << '\n';
    print(std::cout, query.eval(file)) << '\n';
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ex15_39_41 textfile\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }
    const TextQuery file(input);

    const Query word("CMake");
    run_query("word", word, file);
    run_query("negation", ~word, file);
    run_query("or", word | Query("file"), file);
    run_query("and", word & Query("file"), file);
    run_query("combined", word & ~Query("build") | Query("Compilers"), file);
    return 0;
}
