#include <iostream>
#include <numeric>
#include <vector>

// 10.3: sum the elements of a vector<int> with accumulate.
// 10.4: show why accumulate(vec.cbegin(), vec.cend(), 0) on a vector<double>
//       loses the fractional part: the third argument fixes the sum's type.

int main()
{
    std::vector<int> numbers;
    int value = 0;
    while (std::cin >> value)
    {
        numbers.push_back(value);
    }
    std::cout << "integer sum = "
              << std::accumulate(numbers.cbegin(), numbers.cend(), 0) << '\n';

    const std::vector<double> sizes{0.5, 1.5, 2.5};
    int truncated_sum = std::accumulate(sizes.cbegin(), sizes.cend(), 0);
    double exact_sum = std::accumulate(sizes.cbegin(), sizes.cend(), 0.0);
    std::cout << "accumulate with 0   gives " << truncated_sum << '\n';
    std::cout << "accumulate with 0.0 gives " << exact_sum << '\n';
    return 0;
}
