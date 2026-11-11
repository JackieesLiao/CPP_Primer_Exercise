#include <iostream>
#include <string>
#include <vector>

// 2.40-2.41: the chapter-2 Sales_data is a plain struct with data members
// only. Exercise 2.41 repeats 1.20-1.23 on top of it: print every record
// with its average price, then combine consecutive records with the same
// ISBN and report how many records each group holds.

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

void print_record(const Sales_data &item)
{
    std::cout << item.bookNo << ' ' << item.units_sold << ' ' << item.revenue;
    if (item.units_sold != 0)
    {
        std::cout << " average " << item.revenue / item.units_sold;
    }
    std::cout << '\n';
}

int main()
{
    std::vector<Sales_data> records;
    Sales_data item;
    double price = 0.0;
    while (std::cin >> item.bookNo >> item.units_sold >> price)
    {
        item.revenue = item.units_sold * price;
        records.push_back(item);
    }
    if (records.empty())
    {
        std::cerr << "No data.\n";
        return 1;
    }
    for (const Sales_data &record : records)
    {
        print_record(record);
    }

    Sales_data total = records[0];
    unsigned count = 1;
    for (std::size_t index = 1; index < records.size(); ++index)
    {
        if (records[index].bookNo == total.bookNo)
        {
            total.units_sold += records[index].units_sold;
            total.revenue += records[index].revenue;
            ++count;
        }
        else
        {
            print_record(total);
            std::cout << "  combined from " << count << " record(s)\n";
            total = records[index];
            count = 1;
        }
    }
    print_record(total);
    std::cout << "  combined from " << count << " record(s)\n";
    return 0;
}
