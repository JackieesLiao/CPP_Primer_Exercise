#include <iostream>
#include <memory>

// 12.26: allocate an int array with new[n]() so it is value-initialized,
// then manage the memory with unique_ptr<int[]> and with shared_ptr plus
// the array-aware deleter default_delete<int[]>.

int main()
{
    int *values = new int[10]();
    std::cout << "value-initialized:";
    for (int index = 0; index < 10; ++index)
    {
        std::cout << ' ' << values[index];
    }
    std::cout << '\n';
    delete[] values;

    std::unique_ptr<int[]> unique_values(new int[10]);
    for (int index = 0; index < 10; ++index)
    {
        unique_values[index] = index * index;
    }
    std::cout << "unique_ptr:";
    for (int index = 0; index < 10; ++index)
    {
        std::cout << ' ' << unique_values[index];
    }
    std::cout << '\n';

    std::shared_ptr<int> shared_values(new int[10], std::default_delete<int[]>());
    for (int index = 0; index < 10; ++index)
    {
        shared_values.get()[index] = index + 1;
    }
    std::cout << "shared_ptr:";
    for (int index = 0; index < 10; ++index)
    {
        std::cout << ' ' << shared_values.get()[index];
    }
    std::cout << '\n';
    return 0;
}
