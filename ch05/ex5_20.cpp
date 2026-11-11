#include <iostream>
#include <string>

// 5.20: print the first word that appears twice in a row, or report that
// no word repeats.

int main()
{
    std::string word, previous;
    bool found = false;
    while (std::cin >> word)
    {
        if (word == previous)
        {
            found = true;
            break;
        }
        previous = word;
    }
    if (found)
    {
        std::cout << word << " occurs twice in succession\n";
    }
    else
    {
        std::cout << "no word was repeated\n";
    }
    return 0;
}
