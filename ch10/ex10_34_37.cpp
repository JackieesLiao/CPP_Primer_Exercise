#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

// 10.34: print a vector through reverse iterators.
// 10.35: print the same vector backwards with ordinary iterators.
// 10.36: locate the last zero of a list with find over reverse iterators.
// 10.37: copy the elements at positions 3 to 7 of a list, in reverse order,
//        into a vector.

int main()
{
    const std::vector<int> values{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::ostream_iterator<int> out(std::cout, " ");
    std::cout << "10.34 reverse iterators:";
    std::copy(values.crbegin(), values.crend(), out);
    std::cout << '\n';

    std::cout << "10.35 ordinary iterators:";
    for (auto it = values.cend(); it != values.cbegin();)
    {
        --it;
        std::cout << ' ' << *it;
    }
    std::cout << '\n';

    const std::list<int> number_list{0, 1, 2, 3, 4, 0, 6, 7, 0, 9};
    auto last_zero = std::find(number_list.rbegin(), number_list.rend(), 0);
    if (last_zero != number_list.rend())
    {
        auto position = last_zero.base();
        --position;
        std::cout << "10.36 the last zero is at index "
                  << std::distance(number_list.cbegin(), position) << '\n';
    }
    else
    {
        std::cout << "10.36 the list contains no zero\n";
    }

    std::vector<int> copied;
    auto first = number_list.rbegin();
    std::advance(first, 2);
    auto last = number_list.rbegin();
    std::advance(last, 7);
    std::copy(first, last, std::back_inserter(copied));
    std::cout << "10.37 positions 3 to 7 in reverse:";
    for (int value : copied)
    {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
    return 0;
}
