#include <iostream>

// 10.14: a lambda that takes two ints and returns their sum.
// 10.15: a lambda that captures a local int and adds it to its parameter.

int main()
{
    int base = 10;
    auto add = [](int lhs, int rhs)
    {
        return lhs + rhs;
    };
    auto add_base = [base](int value)
    {
        return base + value;
    };
    std::cout << "10.14 add(3, 4) = " << add(3, 4) << '\n';
    std::cout << "10.15 add_base(5) with base " << base
              << " = " << add_base(5) << '\n';
    return 0;
}
