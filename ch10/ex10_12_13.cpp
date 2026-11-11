#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../ch07/Sales_data.h"

// 10.12: sort a vector<Sales_data> by ISBN using a function.
// 10.13: keep the words of length 5 or more in front with partition.

bool compare_isbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

bool at_least_five(const std::string &word)
{
    return word.size() >= 5;
}

Sales_data make_sale(const std::string &isbn, unsigned units_sold, double revenue)
{
    Sales_data item;
    item.bookNo = isbn;
    item.units_sold = units_sold;
    item.revenue = revenue;
    return item;
}

int main()
{
    std::vector<Sales_data> books{
        make_sale("0-201-82470-1", 1, 30.0),
        make_sale("0-201-70353-X", 4, 99.96),
        make_sale("0-201-78345-X", 3, 60.0),
        make_sale("0-201-70353-X", 1, 20.04)};
    std::sort(books.begin(), books.end(), compare_isbn);
    std::cout << "10.12 books sorted by ISBN:" << '\n';
    for (const Sales_data &item : books)
    {
        std::cout << "  " << item.isbn() << " units " << item.units_sold << '\n';
    }

    std::vector<std::string> words{"red", "turtle", "quick", "fox", "jumps", "slow"};
    auto split_point = std::partition(words.begin(), words.end(), at_least_five);
    std::cout << "10.13 words of length 5 or more:";
    for (auto it = words.begin(); it != split_point; ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << "\n10.13 words shorter than 5:";
    for (auto it = split_point; it != words.end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
    return 0;
}
