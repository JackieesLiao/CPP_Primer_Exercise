#include <iostream>
#include <string>

// 18.26/18.27/18.28: name ambiguity in multiple inheritance. Both bases
// declare print(int); in the uncorrected version, calling print(42) on an
// MI object is ambiguous. MI resolves it by defining its own print(int)
// that forwards to Base1::print, and a using declaration would bring both
// overloads into scope (18.27).

class Base1
{
public:
    void print(int value) const
    {
        std::cout << "Base1::print(int) " << value << '\n';
    }

protected:
    int base1_data = 1;
};

class Base2
{
public:
    void print(int value) const
    {
        std::cout << "Base2::print(int) " << value << '\n';
    }

protected:
    int base2_data = 2;
};

class MI : public Base1, public Base2
{
public:
    void print(int value) const;
};

void MI::print(int value) const
{
    std::cout << "MI::print(int) forwards to ";
    Base1::print(value);
}

int main()
{
    MI object;
    object.print(42);
    return 0;
}
