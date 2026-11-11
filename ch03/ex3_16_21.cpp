#include <iostream>
#include <string>
#include <vector>

// 3.16: print the size and elements of the vectors from exercise 3.13.
// 3.21: repeat the printing through iterators.

int main()
{
    std::vector<int> v1;
    std::vector<int> v2(10);
    std::vector<int> v3(10, 42);
    std::vector<int> v4{10};
    std::vector<int> v5{10, 42};
    std::vector<std::string> v6{10};
    std::vector<std::string> v7{10, "hi"};

    std::vector<std::vector<int>> groups{v1, v2, v3, v4, v5};
    for (const std::vector<int> &group : groups)
    {
        std::cout << "size " << group.size() << ':';
        for (const int value : group)
        {
            std::cout << ' ' << value;
        }
        std::cout << '\n';
    }
    for (const std::vector<std::string> &group : {v6, v7})
    {
        std::cout << "size " << group.size() << ':';
        for (const std::string &value : group)
        {
            std::cout << ' ' << value;
        }
        std::cout << '\n';
    }

    std::cout << "3.21 through iterators:\n";
    for (auto it = v3.cbegin(); it != v3.cend(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
    return 0;
}
