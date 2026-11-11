#include <iostream>
#include <string>

#include "Sales_data.h"

// 14.22/14.45: assign a string ISBN straight to a Sales_data, and let the
// conversion operators hand out the ISBN as a string and the revenue as a
// double. 14.46 argues the conversions should be explicit; the demo uses
// them through explicit initializations so the intent stays visible.

int main()
{
    Sales_data item("0-201-70353-X", 4, 24.99);
    item = std::string("0-201-82470-1");
    std::cout << "after string assignment: " << item << '\n';

    const std::string isbn = static_cast<std::string>(item);
    const double revenue = static_cast<double>(item);
    std::cout << "as string: " << isbn << ", as double: " << revenue << '\n';
    return 0;
}
