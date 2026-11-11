#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../ch07/Sales_data.h"

// 10.17: repeat exercises 10.12 and 10.13 with lambdas instead of functions.

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
    auto compare_isbn = [](const Sales_data &lhs, const Sales_data &rhs)
    {
        return lhs.isbn() < rhs.isbn();
    };
    std::sort(books.begin(), books.end(), compare_isbn);
    std::cout << "10.17 books sorted by ISBN with a lambda:" << '\n';
    for (const Sales_data &item : books)
    {
        std::cout << "  " << item.isbn() << " units " << item.units_sold << '\n';
    }

    std::vector<std::string> words{"red", "turtle", "quick", "fox", "jumps", "slow"};
    auto at_least_five = [](const std::string &word)
    {
        return word.size() >= 5;
    };
    auto split_point = std::partition(words.begin(), words.end(), at_least_five);
    std::cout << "10.17 words of length 5 or more:";
    for (auto it = words.begin(); it != split_point; ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << "\n10.17 words shorter than 5:";
    for (auto it = split_point; it != words.end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
    return 0;
}
