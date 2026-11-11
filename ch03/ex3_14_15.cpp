#include <iostream>
#include <string>
#include <vector>

// 3.14: read integers into a vector<int>.
// 3.15: keep reading the rest of the input as words into a vector<string>.
// The first non-integer token ends the integer sequence and starts the words.

int main()
{
    std::vector<int> numbers;
    int value = 0;
    while (std::cin >> value)
    {
        numbers.push_back(value);
    }
    std::cin.clear();

    std::vector<std::string> words;
    std::string word;
    while (std::cin >> word)
    {
        words.push_back(word);
    }

    std::cout << "ints:";
    for (int number : numbers)
    {
        std::cout << ' ' << number;
    }
    std::cout << "\nwords:";
    for (const std::string &entry : words)
    {
        std::cout << ' ' << entry;
    }
    std::cout << '\n';
    return 0;
}
