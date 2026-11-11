#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

// 10.6: fill an existing sequence with zeros using fill_n.
// 10.7(a): copy into a vector only after it is large enough.
// 10.7(b): reserve does not create elements, so write through back_inserter.

void print_ints(const char *label, const std::vector<int> &values)
{
    std::cout << label;
    for (int value : values)
    {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> sequence(5);
    std::fill_n(sequence.begin(), sequence.size(), 0);
    print_ints("10.6 fill_n on an existing sequence:", sequence);

    std::vector<int> destination;
    const std::list<int> source{1, 2, 3, 4};
    destination.resize(source.size());
    std::copy(source.cbegin(), source.cend(), destination.begin());
    print_ints("10.7(a) copy after resize:", destination);

    std::vector<int> filled;
    std::fill_n(std::back_inserter(filled), 10, 0);
    print_ints("10.7(b) fill_n through back_inserter:", filled);
    return 0;
}
