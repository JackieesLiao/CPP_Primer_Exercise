#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

void remove_even(std::list<int> &values)
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
            ++current;
        }
    }
}

void remove_odd(std::vector<int> &values)
{
    auto current = values.begin();
    while (current != values.end())
    {
        if (*current % 2 != 0)
        {
            current = values.erase(current);
        }
        else
        {
            ++current;
        }
    }
}

void remove_odd(std::forward_list<int> &values)
{
    auto previous = values.before_begin();
    auto current = values.begin();
    while (current != values.end())
    {
        if (*current % 2 != 0)
        {
            current = values.erase_after(previous);
        }
        else
        {
            previous = current;
            ++current;
        }
    }
}

void insert_after_match(std::forward_list<std::string> &values, const std::string &target,
                        const std::string &addition)
{
    auto previous = values.before_begin();
    auto current = values.begin();
    while (current != values.end())
    {
        if (*current == target)
        {
            values.insert_after(current, addition);
            return;
        }
        previous = current;
        ++current;
    }
    values.insert_after(previous, addition);
}

int main()
{
    const int source[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    std::list<int> list_values(std::begin(source), std::end(source));
    std::vector<int> vector_values(std::begin(source), std::end(source));
    std::forward_list<int> forward_values(std::begin(source), std::end(source));
    remove_even(list_values);
    remove_odd(vector_values);
    remove_odd(forward_values);

    for (int value : list_values)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    for (int value : vector_values)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    for (int value : forward_values)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    std::forward_list<std::string> words{"alpha", "beta"};
    insert_after_match(words, "alpha", "inserted");
    insert_after_match(words, "missing", "last");
    for (const std::string &word : words)
    {
        std::cout << word << ' ';
    }
    std::cout << '\n';
    return 0;
}
