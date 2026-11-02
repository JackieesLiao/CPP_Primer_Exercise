#include <iostream>
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
    read_and_print(std::cin);
}
