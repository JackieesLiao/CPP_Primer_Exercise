#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

template <typename T>
int compare(const T &left, const T &right)
{
    if (left < right)
    {
        return -1;
    }
    if (right < left)
    {
        return 1;
    }
    return 0;
}

int main()
{
    // 16.37: fixing T permits the int-to-double conversion.
    const double maximum = std::max<double>(3, 4.5);
    std::cout << "maximum: " << maximum << '\n';

    // 16.38: the arguments select a constructor of the specified object type.
    const auto text = std::make_shared<std::string>(4, 'x');
    std::cout << "shared string: " << *text << '\n';

    // 16.39: compare the contents of literals with different lengths.
    std::cout << "compare: " << compare<std::string>("hi", "world") << '\n';
    return 0;
}
