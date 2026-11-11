#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 13.22/13.30/13.31: HasPtr with value semantics, a swap, a less-than
// operator for sort, and a move assignment that exchanges pointers. The
// assignment operator takes its parameter by value, so the same operator
// serves both copy (via the copy constructor) and move (via the move
// constructor); the 13.54 swap-form rvalue assignment is discussed in the README.

class HasPtr
{
    friend void swap(HasPtr &left, HasPtr &right);
    friend bool operator<(const HasPtr &left, const HasPtr &right);

public:
    explicit HasPtr(const std::string &text = std::string())
        : value(new std::string(text))
    {
    }

    HasPtr(const HasPtr &other)
        : value(new std::string(*other.value))
    {
        std::cout << "copy constructor: " << *value << '\n';
    }

    HasPtr(HasPtr &&other) noexcept : value(other.value)
    {
        other.value = nullptr;
        std::cout << "move constructor: " << *value << '\n';
    }

    HasPtr &operator=(HasPtr other) noexcept
    {
        swap(*this, other);
        std::cout << "assignment (copy-and-swap)\n";
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

inline void swap(HasPtr &left, HasPtr &right)
{
    using std::swap;
    swap(left.value, right.value);
}

inline bool operator<(const HasPtr &left, const HasPtr &right)
{
    return *left.value < *right.value;
}

int main()
{
    std::vector<HasPtr> words;
    words.push_back(HasPtr("pear"));
    words.push_back(HasPtr("apple"));
    words.push_back(HasPtr("banana"));
    std::sort(words.begin(), words.end());
    std::cout << "sorted:";
    for (const HasPtr &word : words)
    {
        std::cout << ' ' << word.get();
    }
    std::cout << '\n';

    HasPtr target("old value");
    target = HasPtr("moved value");
    std::cout << "after move assignment: " << target.get() << '\n';
    return 0;
}
