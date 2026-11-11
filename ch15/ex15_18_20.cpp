#include <iostream>

// 15.18/15.19/15.20: which conversions from derived to base are legal
// depends on the inheritance access. The illegal statements are kept as
// comments so the program still compiles.

class Base
{
public:
    void member() const
    {
        std::cout << "Base member\n";
    }
};

class PublicDerived : public Base
{
};

class ProtectedDerived : protected Base
{
};

class PrivateDerived : private Base
{
};

class NestedFromProtected : protected ProtectedDerived
{
};

int main()
{
    PublicDerived public_object;
    ProtectedDerived protected_object;
    PrivateDerived private_object;
    NestedFromProtected nested_object;

    Base *public_pointer = &public_object;
    (void)public_pointer;
    // Base *protected_pointer = &protected_object;  // illegal: protected inheritance
    // Base *private_pointer = &private_object;      // illegal: private inheritance
    // Base *nested_pointer = &nested_object;        // illegal: path passes through protected
    public_object.member();
    std::cout << "only the public-inheritance conversion compiles\n";
    return 0;
}
