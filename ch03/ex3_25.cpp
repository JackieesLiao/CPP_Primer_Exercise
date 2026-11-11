#include <iostream>
#include <iterator>
#include <vector>

// 3.25: count the grades into eleven buckets through iterators instead of
// subscripts: scores 0-9 fall into bucket 0, 90-99 into bucket 9, a perfect
// 100 into bucket 10.

int main()
{
    std::vector<unsigned> buckets(11, 0);
    unsigned score = 0;
    while (std::cin >> score)
    {
        auto it = buckets.begin();
        it += score / 10;
        ++*it;
    }
    for (const unsigned count : buckets)
    {
        std::cout << count << ' ';
    }
    std::cout << '\n';
    return 0;
}
