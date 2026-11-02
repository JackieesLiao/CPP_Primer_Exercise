#include "Sales_data_io.h"
#include <iostream>

int main()
{
    Sales_data total;
    if (!read(std::cin, total))
    {
        std::cerr << "No valid sales record.\n";
        return 1;
    }

    Sales_data transaction;
    while (read(std::cin, transaction))
    {
        if (total.isbn() == transaction.isbn())
        {
            total.combine(transaction);
        }
        else
        {
            print(std::cout, total) << '\n';
            total = transaction;
        }
    }
    print(std::cout, total) << '\n';
    return 0;
}
