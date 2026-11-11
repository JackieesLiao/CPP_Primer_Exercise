#include <iostream>
#include <sstream>
#include <string>

// 16.21/16.22: debug_rep prints a description of its argument; the pointer
// overload is selected for pointer arguments because it is an exact match,
// and it reports the pointed-to value through the const-reference version.

template <typename T>
std::string debug_rep(const T &value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

template <typename T>
std::string debug_rep(T *pointer)
{
    std::ostringstream stream;
    stream << "pointer " << pointer;
    if (pointer)
    {
        stream << " -> " << debug_rep(*pointer);
    }
    else
    {
        stream << " -> null pointer";
    }
    return stream.str();
}

std::string debug_rep(const std::string &text)
{
    return '"' + text + '"';
}

// 16.22's follow-up: streaming a char* prints the characters, not the
// address, so these overloads route C-style strings into the string
// version for a readable report.

std::string debug_rep(char *text)
{
    return debug_rep(std::string(text));
}

std::string debug_rep(const char *text)
{
    return debug_rep(std::string(text));
}

int main()
{
    std::string word("primer");
    std::cout << debug_rep(word) << '\n';
    std::cout << debug_rep(&word) << '\n';
    const char *literal = "literal";
    std::cout << debug_rep(literal) << '\n';
    std::cout << debug_rep(static_cast<std::string *>(nullptr)) << '\n';
    return 0;
}
