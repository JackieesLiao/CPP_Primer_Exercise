#include <iostream>
#include <sstream>
#include <string>

struct SalesRecord
{
    std::string isbn;
    unsigned units_sold = 0;
    double revenue = 0.0;

    SalesRecord() = default;

    explicit SalesRecord(const std::string &book_number) : isbn(book_number)
    {
    }

    SalesRecord(const std::string &book_number, unsigned count, double price)
        : isbn(book_number), units_sold(count), revenue(count * price)
    {
    }

    explicit SalesRecord(std::istream &input)
    {
        double price = 0.0;
        if (input >> isbn >> units_sold >> price)
        {
            revenue = units_sold * price;
        }
    }
};

int main()
{
    SalesRecord empty;
    SalesRecord book("A");
    SalesRecord sale("B", 2, 10.0);
    std::istringstream input("C 3 5.0");
    SalesRecord from_stream(input);
    if (!input)
    {
        std::cerr << "Invalid sales record.\n";
        return 1;
    }
    std::cout << empty.units_sold << ' ' << book.isbn << ' ' << sale.revenue << ' '
              << from_stream.revenue << '\n';
    return 0;
}
