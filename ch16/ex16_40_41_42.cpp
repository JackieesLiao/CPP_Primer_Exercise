#include <iostream>
#include <list>
#include <string>
#include <vector>

// 16.40: fcn3's return type is the element type after conversion to
// whatever *beg + 0 produces, so it works for arithmetic element types
// only. 16.41: sum takes the accumulator type explicitly so an empty range
// still has a well-defined result type. 16.42: the parameter T deduced for
// different argument kinds is listed in the README.

template <typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0)
{
    return *beg;
}

template <typename T, typename It>
T sum(It first, It last, T initial)
{
    while (first != last)
    {
        initial += *first;
        ++first;
    }
    return initial;
}

template <typename T>
void deduce(T value)
{
    std::cout << "deduced parameter holds " << value << '\n';
}

int main()
{
    const std::vector<int> numbers{1, 2, 3, 4};
    std::cout << "fcn3 first element: " << fcn3(numbers.cbegin(), numbers.cend())
              << '\n';
    std::cout << "sum as long: "
              << sum(numbers.cbegin(), numbers.cend(), 0L) << '\n';

    deduce(42);
    const int constant = 7;
    deduce(constant);
    return 0;
}
