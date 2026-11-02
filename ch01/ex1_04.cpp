#include <iostream>

int main()
{
    int v1 = 0, v2 = 0;
    if (std::cin >> v1 >> v2)
    {
        std::cout << "The product of " << v1 << " and " << v2 << " is " << v1 * v2 << std::endl;
        return 0;
    }
    std::cerr << "Expected two integers." << std::endl;
    return 1;
}
