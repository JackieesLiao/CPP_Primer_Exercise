#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Quote.h"

// 15.26: the copy and move traces of Quote. 15.28/15.29: a vector<Quote>
// slices every object to its base and prices with the base rule; a
// vector<shared_ptr<Quote>> keeps the dynamic type and the discounts.

int main()
{
    std::cout << "--- 15.26 copy and move traces\n";
    Quote original("0-201-70353-X", 20.0);
    Quote copied(original);
    Quote moved(std::move(original));
    moved = copied;

    std::cout << "--- 15.28 vector<Quote>\n";
    std::vector<Quote> basket;
    basket.push_back(Bulk_quote("0-201-78345-X", 20.0, 5, 0.2));
    double plain_total = 0.0;
    for (const Quote &item : basket)
    {
        plain_total += item.net_price(10);
    }
    std::cout << "vector<Quote> total: " << plain_total << '\n';

    std::cout << "--- 15.29 vector<shared_ptr<Quote>>\n";
    std::vector<std::shared_ptr<Quote>> better_basket;
    better_basket.push_back(
        std::make_shared<Bulk_quote>("0-201-78345-X", 20.0, 5, 0.2));
    double smart_total = 0.0;
    for (const std::shared_ptr<Quote> &item : better_basket)
    {
        smart_total += item->net_price(10);
    }
    std::cout << "vector<shared_ptr<Quote>> total: " << smart_total << '\n';
    return 0;
}
