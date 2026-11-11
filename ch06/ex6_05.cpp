#include <iostream>

// 6.5: return the absolute value of an int.

int absolute(int value)
{
    if (value < 0)
    {
        return -value;
    }
    return value;
}

int main()
{
    for (const int value : {-5, 0, 7})
    {
        std::cout << "|" << value << "| = " << absolute(value) << '\n';
    }
    return 0;
}
