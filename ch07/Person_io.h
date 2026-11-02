#ifndef CH07_PERSON_IO_H
#define CH07_PERSON_IO_H

#include "Person.h"
#include <istream>
#include <ostream>

inline std::istream &read(std::istream &input, Person &person)
{
    return input >> person.name >> person.address;
}

inline std::ostream &print(std::ostream &output, const Person &person)
{
    return output << person.get_name() << ' ' << person.get_address();
}

#endif
