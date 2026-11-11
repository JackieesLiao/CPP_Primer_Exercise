#include <iostream>
#include <string>
#include <vector>

// 4.27: bitwise and logical operators on two unsigned long values.
// 4.28: the size in bytes of a few common types.

int main()
{
    const unsigned long ul1 = 3, ul2 = 7;
    std::cout << "ul1 & ul2 = " << (ul1 & ul2) << '\n';
    std::cout << "ul1 | ul2 = " << (ul1 | ul2) << '\n';
    std::cout << "ul1 ^ ul2 = " << (ul1 ^ ul2) << '\n';
    std::cout << "ul1 && ul2 = " << (ul1 && ul2) << '\n';

    std::cout << "4.28 sizeof char " << sizeof(char) << ", int " << sizeof(int)
              << ", long " << sizeof(long) << ", double " << sizeof(double)
              << '\n';
    std::string text;
    std::vector<int> numbers;
    std::cout << "4.28 sizeof string " << sizeof(text) << ", vector<int> "
              << sizeof(numbers) << '\n';
    return 0;
}
