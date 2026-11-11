#include <iostream>
#include <limits>
#include <stdexcept>

// 6.3: a factorial function of our own.
// 6.4: an interactive main that asks for a number and prints its factorial.
// long long keeps results such as 20! inside the representable range;
// negative input and out-of-range results are reported separately.

long long factorial(long long value)
{
    if (value < 0)
    {
        throw std::invalid_argument("factorial needs a non-negative input");
    }
    long long result = 1;
    while (value > 1)
    {
        if (result > std::numeric_limits<long long>::max() / value)
        {
            throw std::overflow_error("factorial result is out of range");
        }
        result *= value;
        --value;
    }
    return result;
}

int main()
{
    long long number = 0;
    if (!(std::cin >> number))
    {
        std::cerr << "Expected a number.\n";
        return 1;
    }
    try
    {
        const long long result = factorial(number);
        std::cout << number << "! = " << result << '\n';
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
