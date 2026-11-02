#include <iostream>

int main()
{
    std::cout << "/*";
    std::cout << '\n';
    std::cout << "*/";
    std::cout << '\n';
    // The fourth original statement prints the four characters: space / * space.
    // clang-format off
    std::cout << /* "*/" /* "/*" */;
    // clang-format on
    std::cout << '\n';
    return 0;
}
