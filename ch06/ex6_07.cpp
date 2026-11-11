#include <iostream>

// 6.7: a function that returns how many times it has been called, using a
// local static variable that persists across calls.

unsigned call_count()
{
    static unsigned calls = 0;
    return ++calls;
}

int main()
{
    for (int round = 0; round < 3; ++round)
    {
        std::cout << "call " << call_count() << '\n';
    }
    return 0;
}
