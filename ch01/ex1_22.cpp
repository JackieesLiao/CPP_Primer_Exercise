#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item total, item;
    if (!(std::cin >> total))
    {
        std::cerr << "No data!" << std::endl;
        return 1;
    }
    while (std::cin >> item)
    {
        if (total.isbn() != item.isbn())
        {
            std::cerr << "Records must have the same ISBN." << std::endl;
            return 1;
        }
        total += item;
    }
    std::cout << total << std::endl;
    return 0;
}
