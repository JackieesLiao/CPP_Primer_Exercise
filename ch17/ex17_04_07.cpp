#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "../ch14/Sales_data.h"

// 17.4/17.5/17.6/17.7/17.8: the bookstore grouping rewritten with
// algorithms and tuples. match_items returns (ISBN, records, count); the
// pair version of 17.5 omits the count; 17.6 adds the index parameter.
// 17.8: accumulate over the whole range would silently fold in groups of
// other ISBNs if the file were not sorted, so equal_range is used.

bool compare_isbn(const Sales_data &left, const Sales_data &right)
{
    return left.isbn() < right.isbn();
}

std::tuple<std::string, std::shared_ptr<std::vector<Sales_data>>, std::size_t>
match_items(const std::vector<Sales_data> &transactions,
            std::vector<Sales_data>::const_iterator begin,
            std::vector<Sales_data>::const_iterator end)
{
    auto records = std::make_shared<std::vector<Sales_data>>(begin, end);
    return std::make_tuple(records->front().isbn(), records, records->size());
}

std::pair<std::string, std::shared_ptr<std::vector<Sales_data>>>
match_items_pair(const std::vector<Sales_data> &transactions,
                 std::vector<Sales_data>::const_iterator begin,
                 std::vector<Sales_data>::const_iterator end)
{
    auto records = std::make_shared<std::vector<Sales_data>>(begin, end);
    return std::make_pair(records->front().isbn(), records);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ex17_04_07 transactionfile\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }
    std::vector<Sales_data> transactions;
    Sales_data item;
    while (input >> item)
    {
        transactions.push_back(item);
    }
    std::sort(transactions.begin(), transactions.end(), compare_isbn);

    auto begin = transactions.cbegin();
    while (begin != transactions.cend())
    {
        auto range = std::equal_range(begin, transactions.cend(), *begin,
                                      compare_isbn);
        const auto result = match_items(transactions, range.first, range.second);
        const std::shared_ptr<std::vector<Sales_data>> &records =
            std::get<1>(result);
        const Sales_data total = std::accumulate(
            records->cbegin(), records->cend(), Sales_data(std::get<0>(result)));
        std::cout << std::get<0>(result) << " from " << std::get<2>(result)
                  << " record(s): " << total << '\n';

        const auto pair_result = match_items_pair(transactions, range.first,
                                                  range.second);
        std::cout << "  pair version holds " << pair_result.second->size()
                  << " record(s)\n";
        begin = range.second;
    }
    return 0;
}
