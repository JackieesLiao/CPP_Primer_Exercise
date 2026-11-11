#include <iostream>
#include <string>
#include <vector>

// 5.5: map numeric grades to letter grades with an if/else ladder.
// 5.6: solve the pass/fail part with the conditional operator.

std::string letter_grade(int grade)
{
    const std::vector<int> thresholds{95, 90, 85, 80, 75, 70, 65, 60};
    const std::vector<std::string> suffixes{"A+", "A", "A-", "B+", "B",
                                            "B-", "C+", "C"};
    std::string result = "F";
    std::size_t index = 0;
    while (index < thresholds.size())
    {
        if (grade >= thresholds[index])
        {
            result = suffixes[index];
            break;
        }
        ++index;
    }
    if (grade < 60)
    {
        result = "F";
    }
    return result;
}

int main()
{
    for (const int grade : {100, 96, 92, 88, 82, 77, 71, 66, 61, 55})
    {
        const std::string letter = letter_grade(grade);
        std::cout << "grade " << grade << " -> " << letter << " ("
                  << (letter == "F" ? "fail" : "pass") << ")\n";
    }
    return 0;
}
