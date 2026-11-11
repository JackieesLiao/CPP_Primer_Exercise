#include <iostream>

// 2.18: change the pointed-to object through the pointer, then change the
// pointer itself to address another object.

int main()
{
    int first = 1, second = 2;
    int *pointer = &first;
    *pointer = 10;
    std::cout << "after *pointer = 10, first is " << first << '\n';
    pointer = &second;
    *pointer = 20;
    std::cout << "after pointer = &second and *pointer = 20, second is "
              << second << '\n';
    return 0;
}
