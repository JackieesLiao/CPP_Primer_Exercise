#include <iostream>
#include <list>
#include <vector>

int main()
{
    const std::list<int> integers{1, 2, 3};
    const std::vector<double> from_list(integers.begin(), integers.end());

    const std::vector<int> values{4, 5, 6};
    const std::vector<double> from_vector(values.begin(), values.end());

    for (double value : from_list)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    for (double value : from_vector)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}
