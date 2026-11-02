#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class Date
{
  public:
    explicit Date(const std::string &text)
    {
        if (text.find_first_of("+-") != std::string::npos)
        {
            throw std::invalid_argument("Date components must be unsigned.");
        }
        if (text.find('/') != std::string::npos)
        {
            parse_numeric(text);
        }
        else
        {
            parse_named_month(text);
        }
        validate();
    }

    void print(std::ostream &output) const
    {
        output << year_ << '-' << month_ << '-' << day_;
    }

  private:
    unsigned year_ = 0;
    unsigned month_ = 0;
    unsigned day_ = 0;

    void parse_numeric(const std::string &text)
    {
        std::istringstream input(text);
        char first_separator = 0;
        char second_separator = 0;
        if (!(input >> month_ >> first_separator >> day_ >> second_separator >> year_) ||
            first_separator != '/' || second_separator != '/')
        {
            throw std::invalid_argument("Expected month/day/year.");
        }
        check_end(input);
    }

    void parse_named_month(const std::string &text)
    {
        std::istringstream input(text);
        std::string month_name;
        if (!(input >> month_name >> day_))
        {
            throw std::invalid_argument("Expected a month name and day.");
        }
        if (input.peek() == ',')
        {
            input.get();
        }
        if (!(input >> year_))
        {
            throw std::invalid_argument("Expected a year.");
        }
        check_end(input);

        const std::string names[] = {"January",   "February", "March",    "April",
                                     "May",       "June",     "July",     "August",
                                     "September", "October",  "November", "December"};
        for (unsigned index = 0; index < 12; ++index)
        {
            if (month_name == names[index] || month_name == names[index].substr(0, 3))
            {
                month_ = index + 1;
                return;
            }
        }
        throw std::invalid_argument("Unknown month name.");
    }

    static void check_end(std::istringstream &input)
    {
        input >> std::ws;
        if (!input.eof())
        {
            throw std::invalid_argument("Unexpected trailing data.");
        }
    }

    void validate() const
    {
        if (year_ == 0 || month_ < 1 || month_ > 12 || day_ < 1)
        {
            throw std::invalid_argument("Date is out of range.");
        }
        const unsigned days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        unsigned limit = days[month_ - 1];
        const bool leap_year = year_ % 4 == 0 && (year_ % 100 != 0 || year_ % 400 == 0);
        if (month_ == 2 && leap_year)
        {
            ++limit;
        }
        if (day_ > limit)
        {
            throw std::invalid_argument("Day is out of range.");
        }
    }
};

int main()
{
    std::string text;
    while (std::getline(std::cin, text))
    {
        try
        {
            Date date(text);
            date.print(std::cout);
            std::cout << '\n';
        }
        catch (const std::exception &error)
        {
            std::cerr << "Invalid date: " << error.what() << '\n';
            return 1;
        }
    }
    return 0;
}
