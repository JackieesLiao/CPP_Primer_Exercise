#include <iostream>

// 6.51: three overloads of f report which one each call selects. The
// double version wins for two doubles; calls mixing int and double are
// ambiguous and therefore do not compile, which the commented-out lines
// document.

void f()
{
    std::cout << "f()\n";
}

void f(int value)
{
    std::cout << "f(int " << value << ")\n";
}

void f(int first, int second)
{
    std::cout << "f(int " << first << ", int " << second << ")\n";
}

void f(double first, double second = 0.0)
{
    std::cout << "f(double " << first << ", double " << second << ")\n";
}

int main()
{
    f();
    f(42);
    f(42, 0);
    f(2.56, 3.14);
    // f(2.56, 42);  // ambiguous: exact double/int mismatch on both sides
    return 0;
}
