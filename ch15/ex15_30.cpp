#include <iostream>

#include "Basket.h"

// 15.30: the Basket groups identical ISBNs through the ordered multiset of
// shared_ptrs and prices each group once with print_total.

int main()
{
    Basket basket;
    basket.add_item(Bulk_quote("0-201-70353-X", 20.0, 5, 0.2));
    basket.add_item(Bulk_quote("0-201-70353-X", 20.0, 5, 0.2));
    basket.add_item(Quote("0-201-82470-1", 30.0));
    basket.add_item(Limit_quote("0-201-78345-X", 25.0, 2, 0.3));
    std::cout << "basket holds " << basket.size() << " item(s)\n";
    basket.total_receipt(std::cout);
    return 0;
}
