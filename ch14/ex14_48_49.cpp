#include <iostream>
#include <string>

// 14.47/14.48/14.49: a Date class with an explicit-to-bool style test. An
// operator bool lets an object be used in a condition; a conversion to
// int (14.47's integral) would cause surprising arithmetic, so bool is
// the safe choice here.

class Date
{
public:
    Date() : year(0), month(0), day(0)
    {
    }

    Date(unsigned y, unsigned m, unsigned d)
        : year(y), month(m), day(d)
    {
    }

    operator bool() const
    {
        return year != 0 && month >= 1 && month <= 12 && day >= 1 && day <= 31;
    }

    std::string to_string() const
    {
        return std::to_string(year) + '-' + std::to_string(month) + '-' +
               std::to_string(day);
    }

private:
    unsigned year;
    unsigned month;
    unsigned day;
};

int main()
{
    const Date valid(2026, 11, 5);
    const Date invalid(0, 13, 1);
    std::cout << valid.to_string() << " is valid: " << std::boolalpha
              << static_cast<bool>(valid) << '\n';
    std::cout << invalid.to_string() << " is valid: "
              << static_cast<bool>(invalid) << '\n';
    if (valid)
    {
        std::cout << "the object itself works as a condition\n";
    }
    return 0;
}
