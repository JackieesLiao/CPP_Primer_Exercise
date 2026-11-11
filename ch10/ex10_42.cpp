#include <iostream>
#include <list>
#include <string>

// 10.42: remove duplicate words from a list using the list member algorithms
// sort and unique. The member unique erases the duplicates directly, so no
// call to erase is needed afterwards.

int main()
{
    std::list<std::string> words;
    std::string word;
    while (std::cin >> word)
    {
        words.push_back(word);
    }

    words.sort();
    words.unique();
    std::cout << "after sort and unique:";
    for (const std::string &value : words)
    {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
    return 0;
}
