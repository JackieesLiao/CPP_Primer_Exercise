#include <iostream>
#include <memory>
#include <string>

// 13.27: a reference-counted HasPtr. Copies bump the counter and share the
// string; the destructor releases the storage only for the last user. This
// is the manual version of what shared_ptr does automatically.

class HasPtr
{
public:
    explicit HasPtr(const std::string &text = std::string())
    {
        std::unique_ptr<std::string> owned(new std::string(text));
        use = new std::size_t(1);
        value = owned.release();
    }

    HasPtr(const HasPtr &other)
        : value(other.value), use(other.use)
    {
        ++*use;
    }

    ~HasPtr()
    {
        if (--*use == 0)
        {
            delete value;
            delete use;
        }
    }

    HasPtr &operator=(const HasPtr &other)
    {
        ++*other.use;
        if (--*use == 0)
        {
            delete value;
            delete use;
        }
        value = other.value;
        use = other.use;
        return *this;
    }

    const std::string &get() const
    {
        return *value;
    }

    std::size_t users() const
    {
        return *use;
    }

private:
    // The manually shared count requires external synchronization.
    std::string *value;
    std::size_t *use;
};

int main()
{
    HasPtr first("shared");
    HasPtr second(first);
    HasPtr third;
    third = first;
    std::cout << "after three copies: " << third.get() << " with "
              << third.users() << " user(s)\n";
    {
        HasPtr fourth(first);
        std::cout << "inside block: " << fourth.users() << " user(s)\n";
    }
    std::cout << "after block: " << first.users() << " user(s)\n";
    return 0;
}
