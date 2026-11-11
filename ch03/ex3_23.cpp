#include <iostream>
#include <vector>

// 3.23: put ten numbers into a vector and double each element through an
// iterator, then print the result.

int main()
{
    std::vector<int> values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto it = values.begin(); it != values.end(); ++it)
    {
        *it *= 2;
    }
    for (const int value : values)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}
