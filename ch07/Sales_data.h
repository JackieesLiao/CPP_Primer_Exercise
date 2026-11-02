#ifndef CH07_SALES_DATA_H
#define CH07_SALES_DATA_H

#include <string>

// Initial chapter-7 version: access control and constructors are added later.
struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    std::string isbn() const
    {
        return bookNo;
    }

    double avg_price() const
    {
        if (units_sold == 0)
        {
            return 0.0;
        }
        return revenue / units_sold;
    }

    Sales_data &combine(const Sales_data &rhs)
    {
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
        return *this;
    }
};
#endif
