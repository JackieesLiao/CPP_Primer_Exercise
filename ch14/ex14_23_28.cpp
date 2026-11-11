#include <iostream>
#include <string>

#include "../ch13/StrVec.h"

// 14.23/14.26/14.27/14.28: the initializer-list assignment and the
// subscript operator of StrVec, demonstrated together with the
// chapter-12 StrBlobPtr arithmetic.

int main()
{
    StrVec values;
    values = {"one", "two", "three"};
    std::cout << "after initializer-list assignment:";
    for (std::size_t index = 0; index < values.size(); ++index)
    {
        std::cout << ' ' << values[index];
    }
    std::cout << '\n';
    values[1] = "TWO";
    std::cout << "after subscript write: " << values[1] << '\n';
    return 0;
}
