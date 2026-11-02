#include <iostream>
#include <sstream>
#include <string>
std::istream &read_and_print(std::istream &input)
{
    std::string word;
    while (input >> word)
    {
        std::cout << word << '\n';
    }
    input.clear();
    return input;
}
int main()
{
    std::istringstream input("one two three");
    read_and_print(input);
}
