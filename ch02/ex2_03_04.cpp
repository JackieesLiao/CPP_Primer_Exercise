#include <iostream>

// 2.3: print the results of the book's expressions.
// 2.4: unsigned arithmetic wraps around modulo 2^32, which is well defined,
// so u - u2 prints 4294967264 instead of an error. The mixed cases convert
// the int operand to unsigned before subtracting, hence two zeros.

int main()
{
    unsigned u = 10, u2 = 42;
    std::cout << u2 - u << '\n';
    std::cout << u - u2 << '\n';
    int i = 10, i2 = 42;
    std::cout << i2 - i << '\n';
    std::cout << i - i2 << '\n';
    std::cout << i - u << '\n';
    std::cout << u - i << '\n';
    return 0;
}
