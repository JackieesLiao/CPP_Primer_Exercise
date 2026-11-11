#include <iostream>
#include <string>

#include "../ch13/String.h"

// 14.7: an ostream operator for our chapter-13 String, plus the 14.26
// read-only subscript it grew.

std::ostream &operator<<(std::ostream &output, const String &text)
{
    output << text.c_str();
    return output;
}

int main()
{
    const String text("overloaded output");
    std::cout << text << '\n';
    std::cout << "text[4] = " << text[4] << '\n';
    return 0;
}
