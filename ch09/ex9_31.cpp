#include <forward_list>
#include <iostream>
#include <list>

void transform(std::list<int> &values)
{
    auto current = values.begin();
    while (current != values.end())
    {
        if (*current % 2 == 0)
        {
            current = values.erase(current);
        }
        else
        {
            values.insert(current, *current);
            ++current;
        }
    }
}

void transform(std::forward_list<int> &values)
{
    auto previous = values.before_begin();
    auto current = values.begin();
    while (current != values.end())
    {
        if (*current % 2 == 0)
        {
            current = values.erase_after(previous);
        }
        else
        {
            values.insert_after(previous, *current);
            previous = current;
            ++current;
        }
    }
}

int main()
{
    std::list<int> list_values{0, 1, 2, 3};
    std::forward_list<int> forward_values{0, 1, 2, 3};
    transform(list_values);
    transform(forward_values);
    for (int value : list_values)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    for (int value : forward_values)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}
