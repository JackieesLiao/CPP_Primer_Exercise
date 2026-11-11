#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>

// 14.44: a calculator driven by a map from operator names to
// std::function<int(int, int)>. Invalid operations report an error and
// leave the calculator ready for the next expression.

int checked_result(long long result)
{
    if (result < std::numeric_limits<int>::min() ||
        result > std::numeric_limits<int>::max())
    {
        throw std::overflow_error("result is out of range");
    }
    return static_cast<int>(result);
}

int add(int left, int right)
{
    return checked_result(static_cast<long long>(left) + right);
}

int subtract(int left, int right)
{
    return checked_result(static_cast<long long>(left) - right);
}

int multiply(int left, int right)
{
    return checked_result(static_cast<long long>(left) * right);
}

int divide(int left, int right)
{
    if (right == 0)
    {
        throw std::runtime_error("division by zero");
    }
    return checked_result(static_cast<long long>(left) / right);
}

int main()
{
    const std::map<std::string, std::function<int(int, int)>> operations{
        {"+", add},
        {"-", subtract},
        {"*", multiply},
        {"/", divide}};
    int left = 0, right = 0;
    std::string operation;
    while (std::cin >> left >> operation >> right)
    {
        auto selected = operations.find(operation);
        if (selected == operations.end())
        {
            std::cout << "unsupported operator: " << operation << '\n';
            continue;
        }
        try
        {
            const int result = selected->second(left, right);
            std::cout << left << ' ' << operation << ' ' << right << " = " << result << '\n';
        }
        catch (const std::runtime_error &error)
        {
            std::cout << error.what() << '\n';
        }
    }
    return 0;
}
