#include <iostream>
#include <vector>

#include "Sales_data.h"

// 2.42: repeat the 2.41 program through the Sales_data.h header and its
// read and print helpers.

int main()
{
    std::vector<Sales_data> records;
    Sales_data item;
    while (read(std::cin, item))
    {
        records.push_back(item);
    }
    if (records.empty())
    {
        std::cerr << "No data.\n";
        return 1;
    }
    for (const Sales_data &record : records)
    {
        print(std::cout, record);
        std::cout << '\n';
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
            print(std::cout, total);
            std::cout << "  combined from " << count << " record(s)\n";
            total = records[index];
            count = 1;
        }
    }
    print(std::cout, total);
    std::cout << "  combined from " << count << " record(s)\n";
    return 0;
}
