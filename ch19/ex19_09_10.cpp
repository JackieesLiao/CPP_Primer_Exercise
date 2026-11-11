#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

// 19.9: print the sizes of a few types through typeid. MSVC prints
// decorated names such as "class std::vector<int,class std::allocator<int> >".

class Quote
{
};

class Bulk_quote : public Quote
{
};

int main()
{
    std::cout << "int: " << typeid(int).name() << " size " << sizeof(int) << '\n';
    std::cout << "vector<int>: " << typeid(std::vector<int>).name() << " size "
              << sizeof(std::vector<int>) << '\n';
    std::cout << "Quote: " << typeid(Quote).name() << " size "
              << sizeof(Quote) << '\n';
    std::cout << "Bulk_quote: " << typeid(Bulk_quote).name() << " size "
              << sizeof(Bulk_quote) << '\n';
    return 0;
}
