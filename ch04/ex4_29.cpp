#include <iostream>

// 4.29: sizeof an array yields the whole array's size, so the first ratio
// is the element count. A pointer only knows its own size, so the second
// ratio is 1 on this 64-bit build (pointer and int are 8 and 4 bytes here,
// which still gives 1 or 2 depending on the platform - the ratio is not
// a reliable element count).

int main()
{
    int x[10];
    int *p = x;
    std::cout << sizeof(x) / sizeof(*x) << '\n';
    std::cout << sizeof(p) / sizeof(*p) << '\n';
    std::cout << "sizes: pointer " << sizeof(p) << " bytes, int "
              << sizeof(*p) << " bytes\n";
    return 0;
}
