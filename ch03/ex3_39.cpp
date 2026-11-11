#include <cstring>
#include <iostream>

// 3.39: compare two C-style strings with strcmp and concatenate them with
// strcpy and strcat into a buffer large enough for both plus the terminator.

int main()
{
    const char *first = "hello";
    const char *second = "world";
    int order = std::strcmp(first, second);
    if (order == 0)
    {
        std::cout << "equal\n";
    }
    else if (order < 0)
    {
        std::cout << first << " comes first\n";
    }
    else
    {
        std::cout << second << " comes first\n";
    }

    const std::size_t size = std::strlen(first) + std::strlen(second) + 1;
    char *combined = new char[size];
    std::strcpy(combined, first);
    std::strcat(combined, second);
    std::cout << combined << '\n';
    delete[] combined;
    return 0;
}
