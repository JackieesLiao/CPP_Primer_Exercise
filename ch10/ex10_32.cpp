#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#include "../ch01/Sales_item.h"

// 10.32: rewrite the bookstore program of section 1.6 with vector<Sales_item>
// and algorithms. The transactions are sorted by ISBN, equal_range locates
// each group of identical ISBNs, and accumulate sums every group.

bool compare_isbn(const Sales_item &lhs, const Sales_item &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ex10_32 transactionfile\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }

    std::istream_iterator<Sales_item> reader(input), eof;
    std::vector<Sales_item> transactions(reader, eof);
    if (transactions.empty())
    {
        std::cerr << "No transactions were read.\n";
        return 1;
    }

    std::sort(transactions.begin(), transactions.end(), compare_isbn);
    auto begin = transactions.begin();
    while (begin != transactions.end())
    {
        auto range = std::equal_range(begin, transactions.end(), *begin,
                                      compare_isbn);
        std::cout << std::accumulate(range.first, range.second,
                                     Sales_item(begin->isbn()))
                  << '\n';
        begin = range.second;
    }
    return 0;
}
