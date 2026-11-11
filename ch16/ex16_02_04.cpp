#include <iostream>
#include <list>
#include <string>
#include <vector>

// 16.2: find and find_last as function templates; 16.4: find works on any
// iterator range, not just containers.

template <typename It, typename T>
It find_value(It first, It last, const T &target)
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

template <typename T>
std::size_t find_last(const std::vector<T> &values, const T &target)
{
    for (std::size_t index = values.size(); index > 0; --index)
    {
        if (values[index - 1] == target)
        {
            return index - 1;
        }
    }
    return values.size();
}

int main()
{
    const std::vector<int> numbers{1, 2, 3, 2, 5};
    std::cout << "find 3 at index "
              << find_value(numbers.cbegin(), numbers.cend(), 3) - numbers.cbegin()
              << '\n';
    std::cout << "last 2 at index " << find_last(numbers, 2) << '\n';

    const std::list<std::string> words{"the", "quick", "the"};
    auto found = find_value(words.cbegin(), words.cend(), std::string("the"));
    std::cout << "first \"the\" found: " << (found != words.cend()) << '\n';
    return 0;
}
