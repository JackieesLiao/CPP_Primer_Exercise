#include <iostream>
#include <string>

// 18.13/18.18: an anonymous namespace gives the counter internal linkage,
// the C++ replacement for C's static globals. The lookup demo shows how a
// using declaration pulls one overload of swap in and lets argument-dependent
// lookup find the class-specific swap.

namespace
{
unsigned anonymous_counter = 0;
unsigned bump()
{
    return ++anonymous_counter;
}
}  // namespace

class Widget
{
public:
    explicit Widget(int value) : value(value)
    {
    }

    int get() const
    {
        return value;
    }

private:
    int value;
};

void swap(Widget &left, Widget &right)
{
    const int temporary = left.get();
    left = Widget(right.get());
    right = Widget(temporary);
    std::cout << "class-specific swap ran\n";
}

void swap(Widget &left, int replacement)
{
    left = Widget(replacement);
    std::cout << "widget/int overload ran\n";
}

void widget_swap(Widget &left, Widget &right)
{
    using std::swap;
    swap(left, right);
}

int main()
{
    const unsigned first_call = bump();
    const unsigned second_call = bump();
    std::cout << "anonymous counter: " << first_call << ' ' << second_call
              << '\n';

    Widget first(1), second(2);
    widget_swap(first, second);
    std::cout << "after swap: " << first.get() << ' ' << second.get() << '\n';
    return 0;
}
