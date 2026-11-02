#include <iostream>
#include "Sales_data.h"

int main()
{
    Sales_data total;
    double price = 0;
    if (!(std::cin >> total.bookNo >> total.units_sold >> price))
    {
        return 1;
    }
    total.revenue = total.units_sold * price;
    Sales_data item;
    while (std::cin >> item.bookNo >> item.units_sold >> price)
    {
        item.revenue = item.units_sold * price;
        if (total.isbn() == item.isbn())
        {
            total.combine(item);
        }
        else
        {
            std::cout << total.isbn() << ' ' << total.units_sold << ' ' << total.revenue << ' '
                      << (total.units_sold ? total.revenue / total.units_sold : 0) << '\n';
            total = item;
        }
    }
    std::cout << total.isbn() << ' ' << total.units_sold << ' ' << total.revenue << ' '
              << (total.units_sold ? total.revenue / total.units_sold : 0) << '\n';
}
