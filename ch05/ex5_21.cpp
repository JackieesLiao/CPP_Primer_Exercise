#include <cctype>
#include <iostream>
#include <string>

// 5.21: like 5.20, but a repeating word only counts when it begins with
// an uppercase letter. Even skipped words interrupt consecutive repeats.

int main()
{
    std::string word, previous;
    bool found = false;
    while (std::cin >> word)
    {
        if (word.empty() || !std::isupper(static_cast<unsigned char>(word[0])))
        {
            previous = word;
            continue;
        }
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
