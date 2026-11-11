#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

// 10.27: build a duplicate-free list with unique_copy and back_inserter.
// 10.28: copy one vector into three lists with inserter, back_inserter and
// front_inserter to see the three output orders.

void print_list(const char *label, const std::list<int> &values)
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
    std::vector<int> raw{1, 2, 3, 2, 1, 4, 4, 5};
    std::sort(raw.begin(), raw.end());
    std::list<int> unique_values;
    std::unique_copy(raw.cbegin(), raw.cend(), std::back_inserter(unique_values));
    print_list("10.27 unique_copy:", unique_values);

    const std::vector<int> source{1, 2, 3, 4, 5};
    std::list<int> inserted;
    std::copy(source.cbegin(), source.cend(), std::inserter(inserted, inserted.end()));
    print_list("10.28 inserter at end:", inserted);

    std::list<int> appended;
    std::copy(source.cbegin(), source.cend(), std::back_inserter(appended));
    print_list("10.28 back_inserter:", appended);

    std::list<int> prepended;
    std::copy(source.cbegin(), source.cend(), std::front_inserter(prepended));
    print_list("10.28 front_inserter:", prepended);
    return 0;
}
