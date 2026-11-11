#include <iostream>
#include <string>

// 5.14: read a sequence of words and report the word that repeats most
// often in immediate succession together with the count. If no word
// repeats, say so.

int main()
{
    std::string word, current_word, best_word;
    unsigned current_count = 0, best_count = 0;
    while (std::cin >> word)
    {
        if (word == current_word)
        {
            ++current_count;
        }
        else
        {
            current_count = 1;
            current_word = word;
        }
        if (current_count > best_count)
        {
            best_count = current_count;
            best_word = current_word;
        }
    }
    if (best_count > 1)
    {
        std::cout << best_word << " occurred " << best_count
                  << " times in a row\n";
    }
    else
    {
        std::cout << "no word was repeated\n";
    }
    return 0;
}
