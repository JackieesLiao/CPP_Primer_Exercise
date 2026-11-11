#include <iostream>
#include <limits>
#include <stdexcept>

// 5.23 is the plain version without any check.
// 5.24 throws a runtime_error when the divisor is zero.
// 5.25 catches that exception, reports it and asks for a new pair until
// the input ends.

int main()
{
    int dividend = 0, divisor = 0;
    std::cout << "two integers (dividend divisor): " << std::flush;
    while (std::cin >> dividend >> divisor)
    {
        try
        {
            if (divisor == 0)
            {
                throw std::runtime_error("division by zero");
            }
            if (dividend == std::numeric_limits<int>::min() && divisor == -1)
            {
                throw std::overflow_error("quotient is out of range");
            }
            std::cout << dividend << " / " << divisor << " = "
                      << dividend / divisor << '\n';
        }
        catch (const std::runtime_error &error)
        {
            std::cout << "caught: " << error.what() << ", try again\n";
        }
        std::cout << "two integers (dividend divisor): " << std::flush;
    }
    return 0;
}
