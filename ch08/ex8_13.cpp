#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
struct PersonInfo
{
    std::string name;
    std::vector<std::string> phones;
};
// Demonstration rule: accept exactly ten ASCII digits.
bool valid(const std::string &phone)
{
    if (phone.size() != 10)
    {
        return false;
    }
    for (char c : phone)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }
    return true;
}
std::string format(const std::string &phone)
{
    return phone.substr(0, 3) + '-' + phone.substr(3, 3) + '-' + phone.substr(6);
}
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ex8_13 FILE\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open input\n";
        return 1;
    }
    std::vector<PersonInfo> people;
    std::string line, number;
    while (std::getline(input, line))
    {
        std::istringstream record(line);
        PersonInfo info;
        if (!(record >> info.name))
        {
            continue;
        }
        while (record >> number)
        {
            info.phones.push_back(number);
        }
        people.push_back(info);
    }
    if (input.bad())
    {
        return 1;
    }
    for (const auto &person : people)
    {
        std::ostringstream formatted, invalid;
        for (const auto &phone : person.phones)
        {
            if (valid(phone))
            {
                formatted << ' ' << format(phone);
            }
            else
            {
                invalid << ' ' << phone;
            }
        }
        if (invalid.str().empty())
        {
            std::cout << person.name << formatted.str() << '\n';
        }
        else
        {
            std::cerr << "input error: " << person.name << invalid.str() << '\n';
        }
    }
}
