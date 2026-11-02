#include <fstream>
#include <iostream>
#include <string>
#include "../ch07/Sales_data.h"

bool read(std::istream &in, Sales_data &item)
{
    double price = 0;
    if (!(in >> item.bookNo >> item.units_sold >> price))
    {
        return false;
    }
    item.revenue = item.units_sold * price;
    return true;
}
void print(std::ostream &out, const Sales_data &item)
{
    out << item.isbn() << ' ' << item.units_sold << ' ' << item.revenue << ' '
        << (item.units_sold ? item.revenue / item.units_sold : 0) << '\n';
}
int main(int argc, char **argv)
{
    if (argc < 2 || argc > 4 || (argc == 4 && std::string(argv[3]) != "--append"))
    {
        std::cerr << "Usage: program INPUT [OUTPUT [--append]]\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open input\n";
        return 1;
    }
    std::ofstream file;
    if (argc >= 3)
    {
        file.open(argv[2], argc == 4 ? std::ios::app : std::ios::out);
        if (!file)
        {
            std::cerr << "Cannot open output\n";
            return 1;
        }
    }
    std::ostream &out = argc >= 3 ? file : std::cout;
    Sales_data total, item;
    if (!read(input, total))
    {
        std::cerr << "No data or invalid record\n";
        return 1;
    }
    while (read(input, item))
    {
        if (total.isbn() == item.isbn())
        {
            total.combine(item);
        }
        else
        {
            print(out, total);
            total = item;
        }
    }
    if (input.bad() || (!input.eof() && input.fail()))
    {
        std::cerr << "Invalid input or IO error\n";
        return 1;
    }
    print(out, total);
    if (!out)
    {
        std::cerr << "Output error\n";
        return 1;
    }
}
