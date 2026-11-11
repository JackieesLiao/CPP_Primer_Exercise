#include <algorithm>
#include <iostream>
#include <vector>

// 13.56-13.58: reference-qualified member functions. The rvalue version
// may sort in place; the const lvalue version copies first. Calling
// sorted() on the temporary Foo().sorted() would pick the && version.
// The 13.56 variant that returns ret.sorted() recurses forever because
// ret is an lvalue and binds to the const & overload again.

class Foo
{
public:
    explicit Foo(std::vector<int> values) : data(std::move(values))
    {
    }

    Foo sorted() &&
    {
        std::sort(data.begin(), data.end());
        std::cout << "sorted() && ran\n";
        return *this;
    }

    Foo sorted() const &
    {
        std::cout << "sorted() const & ran\n";
        Foo copied(*this);
        std::sort(copied.data.begin(), copied.data.end());
        return copied;
    }

    const std::vector<int> &peek() const
    {
        return data;
    }

private:
    std::vector<int> data;
};

void print_values(const char *label, const std::vector<int> &values)
{
    std::cout << label;
    for (const int value : values)
    {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
}

int main()
{
    Foo object({3, 1, 2});
    Foo copied = object.sorted();
    print_values("const & result:", copied.peek());
    print_values("original untouched:", object.peek());

    Foo moved = Foo({5, 4, 6}).sorted();
    print_values("&& result:", moved.peek());
    return 0;
}
