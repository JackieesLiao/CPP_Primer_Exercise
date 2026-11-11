#include <iostream>
#include <string>
#include <vector>

// 14.34: a function object that behaves like the conditional operator.
// 14.35/14.36: ReadString reads one line each time it is called and can
// fill a vector straight from a while condition.

class IfThenElse
{
public:
    std::string operator()(bool condition, const std::string &then_value,
                           const std::string &else_value) const
    {
        if (condition)
        {
            return then_value;
        }
        return else_value;
    }
};

class ReadString
{
public:
    explicit ReadString(std::istream &source) : input(source)
    {
    }

    std::string operator()()
    {
        std::string line;
        if (!std::getline(input, line))
        {
            return std::string();
        }
        return line;
    }

private:
    std::istream &input;
};

int main()
{
    const IfThenElse choose;
    std::cout << "choose(true): " << choose(true, "yes", "no") << ", choose(false): "
              << choose(false, "yes", "no") << '\n';

    ReadString read(std::cin);
    std::vector<std::string> lines;
    std::string line;
    while ((line = read()) != std::string())
    {
        lines.push_back(line);
    }
    std::cout << "read " << lines.size() << " line(s)\n";
    return 0;
}
