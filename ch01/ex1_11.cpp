#include <iostream>

int main()
{
    int first = 0, last = 0;
    if (!(std::cin >> first >> last))
    {
        std::cerr << "Expected two integers." << std::endl;
        return 1;
    }
    // This exercise assumes first <= last; exercise 1.19 removes that limit.
    if (first > last)
    {
        std::cerr << "Expected first <= last." << std::endl;
        return 1;
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
