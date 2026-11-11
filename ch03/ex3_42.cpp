#include <iostream>
#include <string>
#include <vector>

// 3.42: copy a vector<string> into an array of C-style strings. The array
// is filled through pointers to its char* elements; c_str() hands out each
// null-terminated copy.

int main()
{
    const std::vector<std::string> words{"hello", "world", "primer"};
    const char *lines[3];
    for (std::size_t index = 0; index < words.size(); ++index)
    {
        lines[index] = words[index].c_str();
    }
    for (std::size_t index = 0; index < 3; ++index)
    {
        std::cout << lines[index] << ' ';
    }
    std::cout << '\n';
    return 0;
}
