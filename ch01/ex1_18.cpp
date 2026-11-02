#include <iostream>

int main()
{
    int current = 0, value = 0;
    if (std::cin >> current)
    {
        int count = 1;
        while (std::cin >> value)
        {
            if (value == current)
            {
                ++count;
            }
            else
            {
                std::cout << current << " occurs " << count << " times" << std::endl;
                current = value;
                count = 1;
            }
        }
        std::cout << current << " occurs " << count << " times" << std::endl;
    }
    return 0;
}
