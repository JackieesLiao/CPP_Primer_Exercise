#include <iostream>
#include <string>

#include "Screen.h"

// 16.14/16.15: the stream operators of Screen. Reading takes height,
// width and a pattern word that is tiled across the screen.

int main()
{
    Screen printed(3, 8, 'x');
    std::cout << printed << '\n';

    Screen read;
    if (std::cin >> read)
    {
        std::cout << "read back:\n" << read;
    }
    return 0;
}
