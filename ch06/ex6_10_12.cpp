#include <iostream>

// 6.10: swap two ints through pointers.
// 6.12: the same through references, which reads better at the call site.

void swap_pointers(int *first, int *second)
{
    const int temporary = *first;
    *first = *second;
    *second = temporary;
}

void swap_references(int &first, int &second)
{
    const int temporary = first;
    first = second;
    second = temporary;
}

int main()
{
    int left = 3, right = 8;
    swap_pointers(&left, &right);
    std::cout << "after swap_pointers: " << left << ' ' << right << '\n';
    swap_references(left, right);
    std::cout << "after swap_references: " << left << ' ' << right << '\n';
    return 0;
}
