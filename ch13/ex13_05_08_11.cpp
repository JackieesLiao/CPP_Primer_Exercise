#include <iostream>
#include <string>

// 13.5/13.8/13.11: a value-like HasPtr with its own copy constructor,
// copy assignment and destructor. The copy constructor allocates a new
// string so the copies never share storage; the assignment operator
// allocates before releasing, which makes self-assignment safe.

class HasPtr
{
public:
    explicit HasPtr(const std::string &text = std::string())
        : value(new std::string(text))
    {
    }

    HasPtr(const HasPtr &other)
        : value(new std::string(*other.value))
    {
    }

    HasPtr &operator=(const HasPtr &other)
    {
        auto new_value = new std::string(*other.value);
        delete value;
        value = new_value;
        return *this;
    }

    ~HasPtr()
    {
        delete value;
    }

    const std::string &get() const
    {
        return *value;
    }

private:
    std::string *value;
};

int main()
{
    HasPtr first("primer");
    HasPtr copy(first);
    HasPtr assigned;
    assigned = first;
    assigned = assigned;
    std::cout << "first: " << first.get() << ", copy: " << copy.get()
              << ", assigned: " << assigned.get() << '\n';
    return 0;
}
