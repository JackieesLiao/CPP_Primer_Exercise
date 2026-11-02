#ifndef CH07_SALES_DATA_IO_H
#define CH07_SALES_DATA_IO_H

#include "Sales_data.h"
#include <istream>
#include <ostream>

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
    double average = 0.0;
    if (item.units_sold != 0)
    {
        average = item.revenue / item.units_sold;
    }
    output << item.isbn() << ' ' << item.units_sold << ' ' << item.revenue << ' ' << average;
    return output;
}

inline Sales_data add(const Sales_data &left, const Sales_data &right)
{
    Sales_data sum = left;
    sum.combine(right);
    return sum;
}

#endif
