#include <iostream>
#include <string>

// 6.44: mark the length comparison as inline; the definition must stay in
// a header when shared across translation units.

inline bool is_shorter(const std::string &lhs, const std::string &rhs)
{
    return lhs.size() < rhs.size();
}

int main()
{
    const std::string first = "quick";
    const std::string second = "turtle";
    std::cout << "is_shorter(quick, turtle): " << is_shorter(first, second) << '\n';
    return 0;
}
