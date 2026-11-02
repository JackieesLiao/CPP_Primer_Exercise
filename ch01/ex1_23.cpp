#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item current, item;
    if (std::cin >> current)
    {
        int count = 1;
        while (std::cin >> item)
        {
            if (item.isbn() == current.isbn())
            {
                ++count;
            }
            else
            {
                std::cout << current.isbn() << " " << count << std::endl;
                current = item;
                count = 1;
            }
        }
        std::cout << current.isbn() << " " << count << std::endl;
    }
    return 0;
}
