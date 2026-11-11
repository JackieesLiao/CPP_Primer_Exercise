#include <cstring>
#include <iostream>
#include <string>
#include <vector>

// 16.63/16.64: the generic count and its overload for C-style strings,
// which compares element by element with strcmp instead of pointer
// equality. 16.65's explicit specialization is discussed in the README.

template <typename T>
int count_values(const std::vector<T> &values, const T &target)
{
    int matches = 0;
    for (const T &value : values)
    {
        if (value == target)
        {
            ++matches;
        }
    }
    return matches;
}

int count_values(const std::vector<const char *> &values, const char *target)
{
    int matches = 0;
    for (const char *value : values)
    {
        if (std::strcmp(value, target) == 0)
        {
            ++matches;
        }
    }
    return matches;
}

int main()
{
    const std::vector<int> numbers{1, 2, 3, 2, 2};
    std::cout << "count 2: " << count_values(numbers, 2) << '\n';

    const std::vector<const char *> words{"alpha", "beta", "alpha"};
    std::cout << "count alpha: " << count_values(words, "alpha") << '\n';

    const std::vector<std::string> text{"one", "two"};
    std::cout << "count \"one\": " << count_values(text, std::string("one")) << '\n';
    return 0;
}
