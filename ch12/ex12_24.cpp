#include <iostream>

// 12.24: read an unknown number of characters into a dynamically allocated
// array. The array doubles whenever one more character would not fit, and
// the old block is released with delete[] before the new one takes over.

int main()
{
    std::size_t capacity = 8;
    char *text = new char[capacity];
    std::size_t size = 0;
    char character = 0;
    while (std::cin.get(character) && character != '\n')
    {
        if (size + 1 >= capacity)
        {
            const std::size_t larger = capacity * 2;
            char *grown = new char[larger];
            for (std::size_t index = 0; index < size; ++index)
            {
                grown[index] = text[index];
            }
            delete[] text;
            text = grown;
            capacity = larger;
        }
        text[size] = character;
        ++size;
    }
    text[size] = '\0';
    std::cout << "read " << size << " characters: " << text << '\n';
    delete[] text;
    return 0;
}
