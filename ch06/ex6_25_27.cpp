#include <iostream>
#include <string>

// 6.25: concatenate the command line arguments into one string.
// 6.26: print each argument on its own line.
// 6.27: sum an initializer_list of ints.

int sum(const std::initializer_list<int> &values)
{
    int total = 0;
    for (const int value : values)
    {
        total += value;
    }
    return total;
}

int main(int argc, char *argv[])
{
    std::string joined;
    for (int index = 1; index < argc; ++index)
    {
        joined += argv[index];
    }
    std::cout << "6.25 joined: " << joined << '\n';

    for (int index = 0; index < argc; ++index)
    {
        std::cout << "6.26 argv[" << index << "] = " << argv[index] << '\n';
    }

    std::cout << "6.27 sum {1, 2, 3, 4} = " << sum({1, 2, 3, 4}) << '\n';
    return 0;
}
