#include <cstring>
#include <iostream>
#include <string>

// 12.23: concatenate two character arrays into a dynamically allocated
// array sized for both plus the terminator, then do the same job with
// string, which sizes and releases its memory on its own.

int main()
{
    const char *first = "hello, ";
    const char *second = "world";
    const std::size_t total = std::strlen(first) + std::strlen(second) + 1;
    char *combined = new char[total];
    std::strcpy(combined, first);
    std::strcat(combined, second);
    std::cout << combined << '\n';
    delete[] combined;

    const std::string joined = std::string(first) + second;
    std::cout << joined << '\n';
    return 0;
}
