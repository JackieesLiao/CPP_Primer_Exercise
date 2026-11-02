#include <iostream>

int main()
{
    int first = 0, last = 0;
    if (!(std::cin >> first >> last) || first > last)
    {
        std::cerr << "Expected two integers with first <= last." << std::endl;
        return 1;
    }
    for (int value = first; value < last; ++value)
    {
        std::cout << value << std::endl;
    }
    std::cout << last << std::endl;
    return 0;
}
