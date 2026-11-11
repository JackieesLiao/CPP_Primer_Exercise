#include <iostream>
#include <iterator>
#include <vector>

// 3.35: set every element of an array to zero through pointers.
// 3.36: compare two arrays and two vectors for equality; arrays are
// compared element by element with pointer arithmetic, not with ==.

bool arrays_equal(const int *first_begin, const int *first_end,
                  const int *second_begin, const int *second_end)
{
    if (first_end - first_begin != second_end - second_begin)
    {
        return false;
    }
    for (const int *left = first_begin, *right = second_begin;
         left != first_end; ++left, ++right)
    {
        if (*left != *right)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int values[5] = {1, 2, 3, 4, 5};
    for (int *it = std::begin(values); it != std::end(values); ++it)
    {
        *it = 0;
    }
    std::cout << "zeroed:";
    for (const int value : values)
    {
        std::cout << ' ' << value;
    }
    std::cout << '\n';

    const int left[3] = {1, 2, 3};
    const int right[3] = {1, 2, 3};
    const int other[3] = {1, 2, 4};
    std::cout << "left == right: "
              << arrays_equal(std::begin(left), std::end(left),
                              std::begin(right), std::end(right))
              << '\n';
    std::cout << "left == other: "
              << arrays_equal(std::begin(left), std::end(left),
                              std::begin(other), std::end(other))
              << '\n';

    const std::vector<int> first{1, 2, 3};
    const std::vector<int> second{1, 2, 3};
    std::cout << "vectors equal: " << (first == second) << '\n';
    return 0;
}
