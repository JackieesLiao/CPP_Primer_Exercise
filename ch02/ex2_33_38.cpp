#include <iostream>

// 2.33-2.38: what auto and decltype deduce for the book's declarations.
// a, b and c are plain ints: auto drops the top-level const of ci and the
// reference-ness of cr. d and e are pointers; e points to const int, so the
// pointed-to value is read-only through it. g binds as a reference to ci.
// 2.38 adds decltype: decltype(delta) is plain int, while decltype((delta))
// is int& because the parenthesized expression is an lvalue.

int main()
{
    int i = 42, &r = i;
    auto a = r;
    a = 43;
    const int ci = i, &cr = ci;
    auto b = ci;
    b = 44;
    auto c = cr;
    c = 45;
    auto d = &i;
    auto e = &ci;
    // *e = 0;  // would not compile: e is a pointer to const int
    auto &g = ci;
    std::cout << "i " << i << ", a " << a << ", b " << b << ", c " << c << '\n';
    std::cout << "*d " << *d << ", *e " << *e << ", g " << g << '\n';

    int delta = 4;
    decltype(delta) square_side = delta;
    decltype((delta)) side_ref = delta;
    side_ref = 10;
    std::cout << "delta " << delta << ", square_side " << square_side << '\n';
    return 0;
}
