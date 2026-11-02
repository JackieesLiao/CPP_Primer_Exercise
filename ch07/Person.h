#ifndef CH07_PERSON_H
#define CH07_PERSON_H
#include <string>

struct Person
{
    std::string name;
    std::string address;
    std::string get_name() const
    {
        return name;
    }
    std::string get_address() const
    {
        return address;
    }
};
#endif
