#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

// 10.1: count how many elements of a vector<int> equal a given value.
// 10.2: repeat the count for a list<string> and a given word.

int main()
{
    const std::vector<int> numbers{1, 2, 3, 4, 2, 2};
    int wanted = 0;
    if (!(std::cin >> wanted))
    {
        std::cerr << "Expected an integer.\n";
        return 1;
    }
    std::cout << "value " << wanted << " appears "
              << std::count(numbers.cbegin(), numbers.cend(), wanted)
              << " time(s) in the vector\n";

    const std::list<std::string> words{"the", "quick", "the", "turtle"};
    std::string word;
    if (!(std::cin >> word))
    {
        std::cerr << "Expected a word.\n";
        return 1;
    }
    std::cout << "word \"" << word << "\" appears "
              << std::count(words.cbegin(), words.cend(), word)
              << " time(s) in the list\n";
    return 0;
}
