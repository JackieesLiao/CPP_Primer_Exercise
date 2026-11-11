#include <iostream>
#include <iterator>
#include <vector>

// 3.40: copy an int array into a vector through begin and end.
// 3.41: build a vector<double> from a double array the same way.

int main()
{
    const int numbers[] = {1, 2, 3, 4, 5};
    std::vector<int> from_ints(std::begin(numbers), std::end(numbers));
    for (const int value : from_ints)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    const double sizes[] = {0.5, 1.5, 2.5};
    std::vector<double> from_doubles(std::begin(sizes), std::end(sizes));
    for (const double value : from_doubles)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}
