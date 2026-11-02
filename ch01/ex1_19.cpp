#include <iostream>

int main()
{
    int first = 0, last = 0;
    if (!(std::cin >> first >> last))
    {
        std::cerr << "Expected two integers." << std::endl;
        return 1;
    }
    if (first > last)
    {
        int temporary = first;
        first = last;
        last = temporary;
    }
    int value = first;
    while (value < last)
    {
        std::cout << value << std::endl;
        ++value;
    }
    std::cout << last << std::endl;
    return 0;
}
