#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// 14.42: the standard library function objects with bind.
// (a) count the ints greater than 1024,
// (b) find the first string not equal to "pooh",
// (c) multiply every double by 2.5.

using std::placeholders::_1;

int main()
{
    const std::vector<int> numbers{100, 1024, 2048, 512, 4096};
    auto greater_than_1024 = std::bind(std::greater<int>(), _1, 1024);
    std::cout << "(a) ints greater than 1024: "
              << std::count_if(numbers.cbegin(), numbers.cend(),
                               greater_than_1024)
              << '\n';

    const std::vector<std::string> words{"pooh", "tigger", "pooh", "owl"};
    auto not_pooh = std::bind(std::not_equal_to<std::string>(), _1, "pooh");
    auto found = std::find_if(words.cbegin(), words.cend(), not_pooh);
    std::cout << "(b) first word != pooh: "
              << (found == words.cend() ? "none" : *found) << '\n';

    std::vector<double> sizes{1.0, 2.0, 4.0};
    auto times_2_5 = std::bind(std::multiplies<double>(), _1, 2.5);
    std::transform(sizes.begin(), sizes.end(), sizes.begin(), times_2_5);
    std::cout << "(c) multiplied:";
    for (const double value : sizes)
    {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
    return 0;
}
