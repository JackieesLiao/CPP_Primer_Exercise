#ifndef CH14_SALES_DATA_H
#define CH14_SALES_DATA_H

#include <iostream>
#include <stdexcept>
#include <string>

// 14.2/14.6/14.9/14.22/14.45: the complete Sales_data with overloaded
// arithmetic, relational, IO and conversion operators. The conversions to
// string and double are the implicit conversions of exercise 14.45.

class Sales_data
{
    friend std::istream &operator>>(std::istream &input, Sales_data &item);
    friend std::ostream &operator<<(std::ostream &output, const Sales_data &item);
    friend bool operator==(const Sales_data &left, const Sales_data &right);
    friend bool operator<(const Sales_data &left, const Sales_data &right);
    friend Sales_data operator+(const Sales_data &left, const Sales_data &right);

public:
    Sales_data() : bookNo(), units_sold(0), revenue(0.0)
    {
    }

    explicit Sales_data(const std::string &isbn)
        : bookNo(isbn), units_sold(0), revenue(0.0)
    {
    }

    Sales_data(const std::string &isbn, unsigned sold, double price)
        : bookNo(isbn), units_sold(sold), revenue(sold * price)
    {
    }

    Sales_data &operator+=(const Sales_data &other)
    {
        units_sold += other.units_sold;
        revenue += other.revenue;
        return *this;
    }

    Sales_data &operator=(const std::string &isbn)
    {
        bookNo = isbn;
        units_sold = 0;
        revenue = 0.0;
        return *this;
    }

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

    operator std::string() const
    {
        return bookNo;
    }

    operator double() const
    {
        return revenue;
    }

private:
    std::string bookNo;
    unsigned units_sold;
    double revenue;
};

inline std::istream &operator>>(std::istream &input, Sales_data &item)
{
    double price = 0.0;
    input >> item.bookNo >> item.units_sold >> price;
    if (input)
    {
        item.revenue = item.units_sold * price;
    }
    else
    {
        item = Sales_data();
    }
    return input;
}

inline std::ostream &operator<<(std::ostream &output, const Sales_data &item)
{
    output << item.isbn() << ' ' << item.units_sold << ' ' << item.revenue
           << ' ' << item.avg_price();
    return output;
}

inline bool operator==(const Sales_data &left, const Sales_data &right)
{
    return left.isbn() == right.isbn() && left.units_sold == right.units_sold &&
           left.revenue == right.revenue;
}

inline bool operator!=(const Sales_data &left, const Sales_data &right)
{
    return !(left == right);
}

inline bool operator<(const Sales_data &left, const Sales_data &right)
{
    return left.isbn() < right.isbn();
}

inline Sales_data operator+(const Sales_data &left, const Sales_data &right)
{
    if (left.isbn() != right.isbn())
    {
        throw std::runtime_error("ISBN mismatch in operator+");
    }
    Sales_data sum = left;
    sum += right;
    return sum;
}
#endif
