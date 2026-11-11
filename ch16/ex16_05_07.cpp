#include <iostream>
#include <string>

// 16.5/16.6/16.7: array utilities as templates. The array bound N is
// deduced from the array type itself.

template <typename T, unsigned N>
void print(const T (&values)[N])
{
    for (unsigned index = 0; index < N; ++index)
    {
        std::cout << values[index] << ' ';
    }
    std::cout << '\n';
}

template <typename T, unsigned N>
T *begin_of(T (&values)[N])
{
    return values;
}

template <typename T, unsigned N>
T *end_of(T (&values)[N])
{
    return values + N;
}

template <typename T, unsigned N>
constexpr unsigned size_of(T (&)[N])
{
    return N;
}

int main()
{
    const int numbers[]{1, 2, 3, 4};
    const std::string words[]{"alpha", "beta"};
    print(numbers);
    print(words);
    std::cout << "size via template: " << size_of(numbers) << ", via begin/end: "
              << end_of(numbers) - begin_of(numbers) << '\n';
    return 0;
}
