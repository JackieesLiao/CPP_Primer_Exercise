#include <iostream>
#include <string>

#include "Quote.h"

// 15.3/15.5/15.11/15.23: print_total dispatches through the dynamic type;
// debug() prints every class's data; passing Quote by value slices, so the
// base price rule applies regardless of what was passed.

int main()
{
    Quote plain("0-201-70353-X", 20.0);
    Bulk_quote bulk("0-201-78345-X", 20.0, 5, 0.2);
    Limit_quote limited("0-201-82470-1", 20.0, 3, 0.3);

    print_total(std::cout, plain, 10);
    print_total(std::cout, bulk, 10);
    print_total(std::cout, limited, 10);
    print_total_by_value(std::cout, bulk, 10);

    std::cout << "--- debug output\n";
    plain.debug();
    bulk.debug();
    limited.debug();
    return 0;
}
