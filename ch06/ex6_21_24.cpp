#include <iostream>
#include <iterator>

// 6.21: return the larger of two ints.
// 6.22: swap the values two int pointers point to.
// 6.23: print an array through a begin/end pointer pair, which carries the
// real length with it.
// 6.24 is discussed in the README: a parameter declared const int ia[10]
// is really a const int*, so nothing guarantees ten elements.

int bigger(int first, int second)
{
    return first > second ? first : second;
}

void swap_pointed_values(int *first, int *second)
{
    const int temporary = *first;
    *first = *second;
    *second = temporary;
}

void print_array(const int *begin, const int *end)
{
    while (begin != end)
    {
        std::cout << *begin << ' ';
        ++begin;
    }
    std::cout << '\n';
}

int main()
{
    std::cout << "bigger(3, 8) = " << bigger(3, 8) << '\n';

    int left = 1, right = 2;
    swap_pointed_values(&left, &right);
    std::cout << "after swap: " << left << ' ' << right << '\n';

    const int values[] = {5, 6, 7};
    print_array(std::begin(values), std::end(values));
    return 0;
}
