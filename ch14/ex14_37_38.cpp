#include <iostream>
#include <string>
#include <utility>
#include <vector>

// 14.37: a function object that swaps two values and reports whether the
// swap changed anything.
// 14.38: a predicate that tests strings against a stored length, usable
// with find_if through std::not1-style logic or directly.

class SwapCheck
{
public:
    template <typename T>
    void operator()(T &left, T &right)
    {
        const T old_left = left;
        const T old_right = right;
        std::swap(left, right);
        std::cout << "swap: values "
                  << (old_left == left && old_right == right
                          ? "were already in place"
                          : "changed")
                  << '\n';
    }
};

class SizeCheck
{
public:
    explicit SizeCheck(std::string::size_type limit) : bound(limit)
    {
    }

    bool operator()(const std::string &text) const
    {
        return text.size() == bound;
    }

private:
    std::string::size_type bound;
};

int main()
{
    SwapCheck swap_check;
    int left = 1, right = 2;
    swap_check(left, right);
    int same = 3, also_same = 3;
    swap_check(same, also_same);

    const std::vector<std::string> words{"the", "quick", "red", "fox"};
    const SizeCheck is_two(2);
    std::cout << "words of exactly 2 letters:";
    for (const std::string &word : words)
    {
        if (is_two(word))
        {
            std::cout << ' ' << word;
        }
    }
    std::cout << '\n';
    return 0;
}
