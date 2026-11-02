#include <iostream>
#include <vector>

using ConstIterator = std::vector<int>::const_iterator;

ConstIterator find_value(ConstIterator first, ConstIterator last, int target)
{
    while (first != last)
    {
        if (*first == target)
        {
            return first;
        }
        ++first;
    }
    return last;
}

bool contains(ConstIterator first, ConstIterator last, int target)
{
    return find_value(first, last, target) != last;
}

int main()
{
    const std::vector<int> values{2, 4, 6};
    int target = 0;
    if (!(std::cin >> target))
    {
        std::cerr << "Expected an integer.\n";
        return 1;
    }
    ConstIterator found = find_value(values.begin(), values.end(), target);
    if (found == values.end())
    {
        std::cout << "Not found\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }
    return 0;
}
