#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values;
    auto previous_capacity = values.capacity();
    std::cout << "initial capacity: " << previous_capacity << '\n';
    for (int value = 0; value < 100; ++value)
    {
        values.push_back(value);
        if (values.capacity() != previous_capacity)
        {
            previous_capacity = values.capacity();
            std::cout << "size: " << values.size() << ", capacity: " << previous_capacity << '\n';
        }
    }
    return 0;
}
