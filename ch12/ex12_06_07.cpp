#include <iostream>
#include <memory>
#include <vector>

// 12.6: return a dynamically allocated vector, print it in a second
// function and release it there with delete.
// 12.7: the same flow with shared_ptr, where the release happens
// automatically when the last user goes away.

std::vector<int> *make_values_raw()
{
    return new std::vector<int>{1, 2, 3};
}

void print_and_release_raw(std::vector<int> *values)
{
    for (const int value : *values)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    delete values;
}

std::shared_ptr<std::vector<int>> make_values_shared()
{
    return std::make_shared<std::vector<int>>(std::vector<int>{4, 5, 6});
}

void print_values(const std::shared_ptr<std::vector<int>> &values)
{
    for (const int value : *values)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> *raw = make_values_raw();
    print_and_release_raw(raw);
    print_values(make_values_shared());
    return 0;
}
