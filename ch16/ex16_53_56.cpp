#include <iostream>
#include <string>

// 16.53-16.56: variadic templates. print walks the parameter pack with
// recursion; error_msg forwards any number of messages to print. The
// terminating overload stops the recursion; 16.55 explains why expanding
// the pack in the recursive call is required.

template <typename T>
std::ostream &print(std::ostream &output, const T &value)
{
    return output << value;
}

template <typename T, typename... Args>
std::ostream &print(std::ostream &output, const T &value, const Args &...rest)
{
    output << value << ", ";
    return print(output, rest...);
}

template <typename... Args>
void error_msg(std::ostream &output, const Args &...rest)
{
    print(output, rest...);
    output << '\n';
}

int main()
{
    print(std::cout, "single") << '\n';
    print(std::cout, 1, "two", 3.5, 'c') << '\n';
    error_msg(std::cerr, "error:", 42, "details");
    return 0;
}
