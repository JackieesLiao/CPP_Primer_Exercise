#include <iostream>
#include <list>
#include <string>
#include <vector>

// 16.19: the loop variable must be spelled typename T::size_type; 16.20:
// printing through any iterator pair.

template <typename T>
void print_by_subscript(const T &container)
{
    typename T::size_type index = 0;
    while (index != container.size())
    {
        std::cout << container[index] << ' ';
        ++index;
    }
    std::cout << '\n';
}

template <typename It>
void print_by_iterator(It first, It last)
{
    while (first != last)
    {
        std::cout << *first << ' ';
        ++first;
    }
    std::cout << '\n';
}

int main()
{
    const std::vector<int> numbers{1, 2, 3};
    const std::list<std::string> words{"alpha", "beta"};
    print_by_subscript(numbers);
    print_by_iterator(words.cbegin(), words.cend());
    return 0;
}
