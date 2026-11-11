#include <iostream>
#include <string>

#include "StrVec.h"

// 13.39/13.40: exercise StrVec: push_back, size and capacity during
// reallocation, the initializer-list constructor and copying.

void print_strvec(const char *label, const StrVec &values)
{
    std::cout << label << " size " << values.size() << ", capacity "
              << values.capacity() << ':';
    for (const std::string *it = values.begin(); it != values.end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

int main()
{
    StrVec values;
    values.push_back("first");
    print_strvec("after 1 push", values);
    values.push_back("second");
    print_strvec("after 2 pushes", values);
    values.push_back("third");
    print_strvec("after 3 pushes", values);

    StrVec from_list{"alpha", "beta", "gamma"};
    print_strvec("from initializer list", from_list);

    StrVec copied(from_list);
    print_strvec("copy", copied);
    return 0;
}
