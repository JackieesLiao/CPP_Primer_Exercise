#include <iostream>
#include <vector>

// 5.17: report whether the first vector is a prefix of the second, using
// the shorter length as the comparison range.

int main()
{
    const std::vector<int> first{0, 1, 1, 2};
    const std::vector<int> second{0, 1, 1, 2, 3, 5, 8};
    const std::vector<int> &shorter = first.size() <= second.size() ? first : second;
    const std::vector<int> &longer = first.size() <= second.size() ? second : first;
    bool is_prefix = true;
    for (std::size_t index = 0; index < shorter.size(); ++index)
    {
        if (shorter[index] != longer[index])
        {
            is_prefix = false;
            break;
        }
    }
    std::cout << (is_prefix ? "the shorter vector is a prefix of the longer one"
                            : "the vectors differ before the shorter one ends")
              << '\n';
    return 0;
}
