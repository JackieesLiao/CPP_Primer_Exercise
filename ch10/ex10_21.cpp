#include <iostream>

// 10.21: a lambda that captures a local int by value (mutable), decrements it
// until it reaches 0, and reports whether it has become 0. Once the copy is 0,
// further calls do not decrement anything; the original variable is untouched.

int main()
{
    int countdown = 3;
    auto decrement_to_zero = [countdown]() mutable -> bool
    {
        if (countdown > 0)
        {
            --countdown;
        }
        return countdown == 0;
    };

    while (!decrement_to_zero())
    {
        std::cout << "still counting down\n";
    }
    std::cout << "reached zero\n";
    std::cout << "calling again returns "
              << std::boolalpha << decrement_to_zero() << '\n';
    std::cout << "the original variable is still " << countdown << '\n';
    return 0;
}
