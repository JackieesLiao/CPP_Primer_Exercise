#ifndef CH07_ENCAPSULATED_SALES_DATA_IO_H
#define CH07_ENCAPSULATED_SALES_DATA_IO_H

#include <istream>
#include <ostream>
#include <string>

class Sales_data
{
public:
    std::string isbn() const
    {
        return book_no_;
    }

    Sales_data &combine(const Sales_data &other)
    {
        units_sold_ += other.units_sold_;
        revenue_ += other.revenue_;
        return *this;
    }

    friend std::istream &read(std::istream &input, Sales_data &item);
    friend std::ostream &print(std::ostream &output, const Sales_data &item);

private:
    std::string book_no_;
    unsigned units_sold_ = 0;
    double revenue_ = 0.0;
};

inline std::istream &read(std::istream &input, Sales_data &item)
{
    std::string book_no;
    unsigned units = 0;
    double price = 0.0;
    if (input >> book_no >> units >> price)
    {
        item.book_no_ = book_no;
        item.units_sold_ = units;
        item.revenue_ = units * price;
    }
    return input;
}

inline std::ostream &print(std::ostream &output, const Sales_data &item)
{
    double average = 0.0;
    if (item.units_sold_ != 0)
    {
        average = item.revenue_ / item.units_sold_;
    }
    return output << item.book_no_ << ' ' << item.units_sold_ << ' ' << item.revenue_ << ' '
                  << average;
}

inline Sales_data add(Sales_data left, const Sales_data &right)
{
    left.combine(right);
    return left;
}

#endif
