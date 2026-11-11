#include <iostream>
#include <vector>

// 6.54-6.56: a vector of function pointers holds the arithmetic operations,
// and the switchboard loops over it, calling each one through the pointer.

int add(int first, int second)
{
    return first + second;
}

int subtract(int first, int second)
{
    return first - second;
}

int multiply(int first, int second)
{
    return first * second;
}

int divide(int first, int second)
{
    if (second == 0)
    {
        return 0;
    }
    return first / second;
}

int main()
{
    using Operation = int (*)(int, int);
    const std::vector<Operation> operations{add, subtract, multiply, divide};
    for (const Operation operation : operations)
    {
        std::cout << operation(12, 4) << ' ';
    }
    std::cout << '\n';
    return 0;
}
