#include <iostream>

// 13.13/13.14/13.16: trace construction, copying and destruction of a
// numbered object. The static counter gives every object its own number;
// 13.15 would make the copy constructor assign the next number instead of
// copying it, which this version already does.

struct Numbered
{
    Numbered()
    {
        mysn = ++counter;
        std::cout << "Numbered() creates number " << mysn << '\n';
    }

    Numbered(const Numbered &)
    {
        mysn = ++counter;
        std::cout << "Numbered(const Numbered &) creates number " << mysn << '\n';
    }

    int mysn;
    static unsigned counter;
};

unsigned Numbered::counter = 0;

void pass_by_value(Numbered value)
{
    std::cout << "pass_by_value sees " << value.mysn << '\n';
}

void pass_by_reference(const Numbered &value)
{
    std::cout << "pass_by_reference sees " << value.mysn << '\n';
}

int main()
{
    Numbered a, b = a, c = b;
    pass_by_value(a);
    pass_by_value(b);
    pass_by_value(c);
    pass_by_reference(a);
    pass_by_reference(b);
    return 0;
}
