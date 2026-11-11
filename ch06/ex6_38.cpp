#include <iostream>

// 6.36-6.38: return a pointer to an array of ten ints. A trailing return
// type expresses the type most directly; typedef and decltype spell the
// same type as comments show.

auto arr10() -> int (*)[10]
{
    static int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    return &values;
}

// typedef int ArrayOfTen[10];
// ArrayOfTen *arr10_by_typedef();

// decltype declares the same type once a matching variable exists:
// int odd_elements[10];
// decltype(odd_elements) *arr10_by_decltype();

int main()
{
    int (*row)[10] = arr10();
    for (const int value : *row)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}
