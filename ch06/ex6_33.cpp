#include <iostream>
#include <vector>

// 6.33: print the elements of a vector<int> recursively: handle the
// element at the current index, then recurse past it. The recursion stops
// when the index reaches the size.

void print_vector(const std::vector<int> &values, std::size_t index)
{
    if (index == values.size())
    {
        std::cout << '\n';
        return;
    }
    std::cout << values[index] << ' ';
    print_vector(values, index + 1);
}

int main()
{
    const std::vector<int> values{1, 2, 3, 4, 5};
    print_vector(values, 0);
    return 0;
}
