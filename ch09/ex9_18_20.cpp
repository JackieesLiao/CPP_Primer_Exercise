#include <deque>
#include <iostream>
#include <list>
#include <string>

int main()
{
    std::deque<std::string> words;
    std::string word;
    while (std::cin >> word)
    {
        words.push_back(word);
    }
    for (std::deque<std::string>::const_iterator iter = words.cbegin(); iter != words.cend();
         ++iter)
    {
        std::cout << *iter << '\n';
    }

    const std::list<int> values{1, 2, 3, 4};
    std::deque<int> odd;
    std::deque<int> even;
    for (int value : values)
    {
        if (value % 2 == 0)
        {
            even.push_back(value);
        }
        else
        {
            odd.push_back(value);
        }
    }
    std::cout << "odd:";
    for (int value : odd)
    {
        std::cout << ' ' << value;
    }
    std::cout << "\neven:";
    for (int value : even)
    {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
    return 0;
}
