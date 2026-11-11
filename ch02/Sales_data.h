#ifndef CH02_SALES_DATA_H
#define CH02_SALES_DATA_H

#include <iostream>
#include <string>

// 2.42: the Sales_data struct extracted into its own header, with read and
// print as free functions. Class-level encapsulation is added in chapter 7.

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

inline std::istream &read(std::istream &input, Sales_data &item)
{
    double price = 0.0;
    input >> item.bookNo >> item.units_sold >> price;
    if (input)
    {
        item.revenue = item.units_sold * price;
    }
    return input;
}

inline std::ostream &print(std::ostream &output, const Sales_data &item)
{
    output << item.bookNo << ' ' << item.units_sold << ' ' << item.revenue;
    if (item.units_sold != 0)
    {
        output << " average " << item.revenue / item.units_sold;
    }
    return output;
}
#endif
