#include <iostream>
#include <string>

// 5.9: count vowels in the input.
// 5.10: also count whitespace, tabs and newlines.
// 5.11: count occurrences of ff, fl and fi.
// 5.12: count vowels in both lower and upper case.

int main()
{
    unsigned vowel_count = 0, space_count = 0, pair_count = 0;
    std::string text;
    std::getline(std::cin, text);
    char previous = '\0';
    for (const char current : text)
    {
        const char lowered = static_cast<char>(
            current >= 'A' && current <= 'Z' ? current - 'A' + 'a' : current);
        if (lowered == 'a' || lowered == 'e' || lowered == 'i' ||
            lowered == 'o' || lowered == 'u')
        {
            ++vowel_count;
        }
        else if (current == ' ' || current == '\t' || current == '\n')
        {
            ++space_count;
        }
        if ((previous == 'f' && current == 'f') ||
            (previous == 'f' && current == 'l') ||
            (previous == 'f' && current == 'i'))
        {
            ++pair_count;
        }
        previous = current;
    }
    std::cout << "vowels: " << vowel_count
              << ", whitespace: " << space_count
              << ", ff/fl/fi: " << pair_count << '\n';
    return 0;
}
