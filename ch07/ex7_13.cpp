#include <iostream>
#include <string>

struct SalesRecord
{
    std::string isbn;
    unsigned units_sold = 0;
    double revenue = 0.0;

    explicit SalesRecord(std::istream &input)
    {
        double price = 0.0;
        if (input >> isbn >> units_sold >> price)
        {
            revenue = units_sold * price;
        }
    }

    void combine(const SalesRecord &other)
    {
        units_sold += other.units_sold;
        revenue += other.revenue;
    }
};

void print(const SalesRecord &record)
{
    double average = 0.0;
    if (record.units_sold != 0)
    {
        average = record.revenue / record.units_sold;
    }
    std::cout << record.isbn << ' ' << record.units_sold << ' ' << record.revenue << ' ' << average
              << '\n';
}

int main()
{
    SalesRecord total(std::cin);
    if (!std::cin)
    {
        std::cerr << "No valid sales record.\n";
        return 1;
    }

    while (true)
    {
        SalesRecord transaction(std::cin);
        if (!std::cin)
        {
            break;
        }
        if (total.isbn == transaction.isbn)
        {
            total.combine(transaction);
        }
        else
        {
            print(total);
            total = transaction;
        }
    }
    print(total);
    return 0;
}
