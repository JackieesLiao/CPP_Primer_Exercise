#include <iostream>
#include <stdexcept>
#include <string>

#include "StrBlob.h"

// 12.2: exercise the StrBlob interface: front, back, push_back, pop_back,
// the const overloads and the out_of_range thrown on an empty container.

int main()
{
    StrBlob sentences{"first", "second"};
    std::cout << "front " << sentences.front() << ", back " << sentences.back()
              << '\n';
    sentences.push_back("third");
    std::cout << "after push_back, back is " << sentences.back() << '\n';
    sentences.pop_back();
    std::cout << "size after pop_back: " << sentences.size() << '\n';

    const StrBlob frozen{"constant", "data"};
    std::cout << "const front " << frozen.front() << ", const back "
              << frozen.back() << '\n';

    StrBlob empty_blob;
    try
    {
        empty_blob.front();
    }
    catch (const std::out_of_range &error)
    {
        std::cout << "caught: " << error.what() << '\n';
    }
    return 0;
}
