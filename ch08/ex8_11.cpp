#include <iostream>
#include <sstream>
#include <string>
#include <vector>
struct PersonInfo
{
    std::string name;
    std::vector<std::string> phones;
};
int main()
{
    std::vector<PersonInfo> people;
    std::string line, phone;
    std::istringstream record;
    while (std::getline(std::cin, line))
    {
        record.clear();
        record.str(line);
        PersonInfo info;
        if (!(record >> info.name))
        {
            continue;
        }
        while (record >> phone)
        {
            info.phones.push_back(phone);
        }
        people.push_back(info);
    }
    for (const auto &person : people)
    {
        std::cout << person.name;
        for (const auto &number : person.phones)
        {
            std::cout << ' ' << number;
        }
        std::cout << '\n';
    }
}
