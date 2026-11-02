#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item first, second;
    if (!(std::cin >> first >> second))
    {
        std::cerr << "Expected two sales records." << std::endl;
        return 1;
    }
    if (first.isbn() != second.isbn())
    {
        std::cerr << "Records must have the same ISBN." << std::endl;
        return 1;
    }
    std::cout << first + second << std::endl;
    return 0;
}
