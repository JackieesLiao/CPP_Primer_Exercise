#include <iostream>
#include <string>
#include <vector>

// 3.22: read one paragraph per line and print its first sentence, that is,
// the text up to and including the first period.

int main()
{
    std::string paragraph;
    while (std::getline(std::cin, paragraph))
    {
        if (paragraph.empty())
        {
            break;
        }
        for (auto it = paragraph.begin(); it != paragraph.end(); ++it)
        {
            std::cout << *it;
            if (*it == '.')
            {
                break;
            }
        }
        std::cout << '\n';
    }
    return 0;
}
