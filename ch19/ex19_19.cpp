#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "../ch14/Sales_data.h"

// 19.19: find the first Sales_data whose isbn() equals the target, using
// a pointer to the member function isbn inside find_if.

int main()
{
    const std::vector<Sales_data> records{
        Sales_data("0-201-70353-X", 4, 24.99),
        Sales_data("0-201-78345-X", 3, 20.0),
        Sales_data("0-201-82470-1", 1, 30.0)};
    const std::string wanted = "0-201-78345-X";
    auto found = std::find_if(
        records.cbegin(), records.cend(),
        std::bind(std::equal_to<std::string>(),
                  std::bind(&Sales_data::isbn, std::placeholders::_1), wanted));
    if (found != records.cend())
    {
        std::cout << "first match: " << *found << '\n';
    }
    else
    {
        std::cout << "no match for " << wanted << '\n';
    }
    return 0;
}
