#include <iostream>
#include <string>
#include <vector>

// 4.6: an expression that is true exactly when a number is odd; using
// % 2 != 0 also works for negative values, whose remainder is -1.
// 4.21: double the odd elements of a vector through the conditional operator.
// 4.22: map a numeric grade to four levels, once with nested conditionals
// and once with if statements for comparison.

bool is_odd(int value)
{
    return value % 2 != 0;
}

std::string grade_by_conditional(int grade)
{
    return (grade > 90) ? "high pass"
                        : (grade > 75) ? "pass" : (grade > 60) ? "low pass" : "fail";
}

std::string grade_by_if(int grade)
{
    if (grade > 90)
    {
        return "high pass";
    }
    if (grade > 75)
    {
        return "pass";
    }
    if (grade > 60)
    {
        return "low pass";
    }
    return "fail";
}

int main()
{
    std::cout << "4.6: 7 odd? " << is_odd(7) << ", -3 odd? " << is_odd(-3)
              << ", 4 odd? " << is_odd(4) << '\n';

    std::vector<int> values{1, 2, 3, 4, 5};
    for (auto it = values.begin(); it != values.end(); ++it)
    {
        *it = is_odd(*it) ? *it * 2 : *it;
    }
    std::cout << "4.21 doubled odds:";
    for (const int value : values)
    {
        std::cout << ' ' << value;
    }
    std::cout << '\n';

    for (const int grade : {95, 80, 65, 50})
    {
        std::cout << "4.22 grade " << grade << ": " << grade_by_conditional(grade)
                  << " / " << grade_by_if(grade) << '\n';
    }
    return 0;
}
