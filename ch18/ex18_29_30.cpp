#include <iostream>

// 18.29/18.30: virtual base classes. Each class constructor announces
// itself: the shared virtual base is constructed first (once, by the most
// derived class), then the direct bases left to right, then the body of
// the most derived. Destructors run in the exact reverse order.

class VirtualBase
{
public:
    VirtualBase()
    {
        std::cout << "VirtualBase constructed\n";
    }

    virtual ~VirtualBase()
    {
        std::cout << "VirtualBase destroyed\n";
    }
};

class VD1 : virtual public VirtualBase
{
public:
    VD1()
    {
        std::cout << "VD1 constructed\n";
    }

    ~VD1()
    {
        std::cout << "VD1 destroyed\n";
    }
};

class VD2 : virtual public VirtualBase
{
public:
    VD2()
    {
        std::cout << "VD2 constructed\n";
    }

    ~VD2()
    {
        std::cout << "VD2 destroyed\n";
    }
};

class Final : public VD1, public VD2
{
public:
    Final()
    {
        std::cout << "Final constructed\n";
    }

    ~Final()
    {
        std::cout << "Final destroyed\n";
    }
};

int main()
{
    std::cout << "--- constructing Final\n";
    {
        Final object;
    }
    std::cout << "--- destructed\n";
    return 0;
}
