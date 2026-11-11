#include <iostream>

// 18.20: which f matches depends on the using declarations in scope.
// Only the declarations brought in by the using statements are candidates,
// so f(10) resolves to whatever set of overloads main has seen.

namespace A
{
int f(int value)
{
    return value + 100;
}
}  // namespace A

namespace B
{
double f(double value)
{
    return value * 2;
}
}  // namespace B

double f(double value)
{
    return value * 10;
}

int main()
{
    using A::f;
    std::cout << "with A::f only: " << f(10) << '\n';

    using B::f;
    std::cout << "with A::f and B::f: " << f(10) << '\n';
    return 0;
}
