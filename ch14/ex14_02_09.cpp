#include <iostream>
#include <stdexcept>
#include <string>

#include "Sales_data.h"

// 14.2/14.6/14.9: exercise the Sales_data operators. A record is read with
// the overloaded >> (format: ISBN units price), then printed, combined and
// compared with the overloaded <<, +, +=, == and <.

int main()
{
    Sales_data item;
    if (!(std::cin >> item))
    {
        std::cerr << "Expected a transaction (ISBN units price).\n";
        return 1;
    }
    std::cout << "as read: " << item << '\n';

    const Sales_data same_isbn(item.isbn(), 2, 10.0);
    const Sales_data sum = item + same_isbn;
    std::cout << "plus same-ISBN record: " << sum << '\n';
    std::cout << "equal check: " << (sum == item + same_isbn) << '\n';

    Sales_data other("9-999-99999-9", 1, 5.0);
    std::cout << "less-than by ISBN: " << (sum < other) << '\n';

    try
    {
        const Sales_data mismatched = item + other;
        (void)mismatched;
    }
    catch (const std::runtime_error &error)
    {
        std::cout << "caught: " << error.what() << '\n';
    }
    return 0;
}
