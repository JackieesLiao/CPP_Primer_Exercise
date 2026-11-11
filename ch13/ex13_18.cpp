#include <iostream>
#include <string>

// 13.18/13.19: every Employee gets a unique id from a static counter, and
// copies or assignments would break that invariant, so both are deleted.

class Employee
{
public:
    Employee() : name(), id(next_id++)
    {
    }

    explicit Employee(const std::string &employee_name)
        : name(employee_name), id(next_id++)
    {
    }

    Employee(const Employee &) = delete;
    Employee &operator=(const Employee &) = delete;

    const std::string &get_name() const
    {
        return name;
    }

    unsigned get_id() const
    {
        return id;
    }

private:
    std::string name;
    unsigned id;
    static unsigned next_id;
};

unsigned Employee::next_id = 1;

int main()
{
    Employee alice("Alice");
    Employee bob("Bob");
    Employee unknown;
    std::cout << alice.get_name() << " id " << alice.get_id() << '\n';
    std::cout << bob.get_name() << " id " << bob.get_id() << '\n';
    std::cout << unknown.get_name() << " id " << unknown.get_id() << '\n';
    return 0;
}
