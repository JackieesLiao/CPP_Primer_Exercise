#include <iostream>

// 3.31: fill an array with the numbers 0 through 9.
// 3.32: copy that array into a second array.

int main()
{
    int first[10];
    for (int index = 0; index < 10; ++index)
    {
        first[index] = index;
    }
    int second[10];
    for (int index = 0; index < 10; ++index)
    {
        second[index] = first[index];
    }
    for (const int value : second)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}
