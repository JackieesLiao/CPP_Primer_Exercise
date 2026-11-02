#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class SalesRecord
{
  public:
    SalesRecord() = default;

    SalesRecord(const std::string &number, unsigned count, double price)
        : isbn_(number), units_sold_(count), revenue_(count * price)
    {
    }

    const std::string &isbn() const
    {
        return isbn_;
    }

    bool combine(const SalesRecord &other)
    {
        if (isbn_ != other.isbn_)
        {
            return false;
        }
        units_sold_ += other.units_sold_;
        revenue_ += other.revenue_;
        return true;
    }

    friend std::ostream &print(std::ostream &output, const SalesRecord &record);
    friend std::istream &read(std::istream &input, SalesRecord &record);

  private:
    std::string isbn_;
    unsigned units_sold_ = 0;
    double revenue_ = 0.0;
};

std::ostream &print(std::ostream &output, const SalesRecord &record)
{
    return output << record.isbn_ << ' ' << record.units_sold_ << ' ' << record.revenue_;
}

std::istream &read(std::istream &input, SalesRecord &record)
{
    std::string isbn;
    unsigned count = 0;
    double price = 0.0;
    if (input >> isbn >> count >> price)
    {
        record = SalesRecord(isbn, count, price);
    }
    return input;
}

SalesRecord add(SalesRecord left, const SalesRecord &right)
{
    if (!left.combine(right))
    {
        throw std::invalid_argument("ISBNs must match.");
    }
    return left;
}

class Person
{
  public:
    Person() = default;

    explicit Person(const std::string &name) : name_(name)
    {
    }

    Person(const std::string &name, const std::string &address) : name_(name), address_(address)
    {
    }

    explicit Person(std::istream &input)
    {
        input >> name_ >> address_;
    }

    const std::string &name() const
    {
        return name_;
    }

    const std::string &address() const
    {
        return address_;
    }

    friend std::istream &read(std::istream &input, Person &person);

  private:
    std::string name_;
    std::string address_;
};

std::istream &read(std::istream &input, Person &person)
{
    return input >> person.name_ >> person.address_;
}

std::ostream &print(std::ostream &output, const Person &person)
{
    return output << person.name() << ' ' << person.address();
}

int main()
{
    SalesRecord total("A", 2, 10.0);
    const SalesRecord same("A", 1, 20.0);
    const SalesRecord other("B", 1, 30.0);
    if (!total.combine(same) || total.combine(other))
    {
        std::cerr << "Unexpected ISBN comparison result.\n";
        return 1;
    }
    print(std::cout, total) << '\n';

    const Person person("Alice", "Shanghai");
    std::cout << person.name() << ' ' << person.address() << '\n';
    return 0;
}
