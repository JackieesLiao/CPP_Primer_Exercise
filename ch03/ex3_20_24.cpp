#include <iostream>
#include <vector>

// 3.20: with subscripts, print the sums of adjacent elements and of the
// first and last elements.
// 3.24: repeat both with iterators.

void print_sums_subscript(const std::vector<int> &values)
{
    std::cout << "adjacent sums:";
    for (std::vector<int>::size_type index = 0; index + 1 < values.size(); index += 2)
    {
        std::cout << ' ' << values[index] + values[index + 1];
    }
    std::cout << "\nfirst and last sums:";
    for (std::vector<int>::size_type low = 0, high = values.size() - 1;
         low <= high; ++low, --high)
    {
        if (low == high)
        {
            std::cout << ' ' << values[low];
        }
        else
        {
            std::cout << ' ' << values[low] + values[high];
        }
    }
    std::cout << '\n';
}

void print_sums_iterator(const std::vector<int> &values)
{
    std::cout << "adjacent sums:";
    for (auto left = values.cbegin(); left != values.cend() && left + 1 != values.cend();
         left += 2)
    {
        std::cout << ' ' << *left + *(left + 1);
    }
    std::cout << "\nfirst and last sums:";
    auto first = values.cbegin();
    auto last = values.cend();
    while (first != last)
    {
        --last;
        if (first == last)
        {
            std::cout << ' ' << *first;
            break;
        }
        std::cout << ' ' << *first + *last;
        ++first;
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> values;
    int value = 0;
    while (std::cin >> value)
    {
        values.push_back(value);
    }
    if (values.empty())
    {
        std::cerr << "Expected at least one integer.\n";
        return 1;
    }
    print_sums_subscript(values);
    print_sums_iterator(values);
    return 0;
}
