#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item total;
    if (std::cin >> total)
    {
        Sales_item transaction;
        while (std::cin >> transaction)
        {
            if (total.isbn() == transaction.isbn())
            {
                total += transaction;
            }
            else
            {
                std::cout << total << std::endl;
                total = transaction;
            }
        }
        std::cout << total << std::endl;
    }
    else
    {
        std::cerr << "No data!" << std::endl;
        return -1;
    }
    return 0;
}
