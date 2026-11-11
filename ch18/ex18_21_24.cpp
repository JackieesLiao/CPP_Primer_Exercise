#include <iostream>
#include <string>

// 18.21/18.24/18.25: multiple inheritance. Conversions to a private base
// are illegal even from a derived pointer; the Panda conversions show
// which base paths are reachable. Constructors print their order: virtual
// bases first, then direct bases left to right, then the object itself.

class Base1
{
public:
    void print(int value) const
    {
        std::cout << "Base1::print(int) " << value << '\n';
    }
};

class Base2
{
public:
    void print(double value) const
    {
        std::cout << "Base2::print(double) " << value << '\n';
    }
};

class Derived : public Base1, private Base2
{
};

class Animal
{
public:
    Animal() : name("animal")
    {
    }

    std::string name;
};

class Bear : public Animal
{
public:
    Bear() : name_suffix("bear")
    {
    }

    std::string name_suffix;
};

class Endangered
{
public:
    Endangered() : status("critical")
    {
    }

    std::string status;
};

class Panda : public Bear, public Endangered
{
public:
    Panda() : dance("bamboo dance")
    {
    }

    std::string dance;
};

int main()
{
    Derived derived;
    Base1 *base1_pointer = &derived;
    (void)base1_pointer;
    // Base2 *base2_pointer = &derived;  // illegal: Base2 is a private base
    base1_pointer->print(7);

    Panda panda;
    Animal *animal_pointer = &panda;
    Bear *bear_pointer = &panda;
    Endangered *endangered_pointer = &panda;
    std::cout << animal_pointer->name << ' ' << bear_pointer->name_suffix
              << " does the " << panda.dance << ", status "
              << endangered_pointer->status << '\n';
    return 0;
}
