#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// 17.37/17.38/17.39: time formatting and parsing. put_time writes a
// tm in a given pattern; get_time reads one back from a string. 17.39's
// program parses "Year Month Day" triples from standard input and prints
// them in long form.

bool parse_date(const std::string &line, std::tm &date)
{
    std::istringstream stream(line);
    if (!(stream >> std::get_time(&date, "%Y %m %d")))
    {
        return false;
    }
    stream >> std::ws;
    if (!stream.eof())
    {
        return false;
    }

    const int year = date.tm_year + 1900;
    const int month = date.tm_mon;
    if (year < 1 || month < 0 || month > 11)
    {
        return false;
    }
    const int month_lengths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool leap_year = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    const int days = month_lengths[month] + (month == 1 && leap_year ? 1 : 0);
    if (date.tm_mday < 1 || date.tm_mday > days)
    {
        return false;
    }

    // Count leap days through the previous February. The offsets account
    // for the days in the preceding months, modulo seven.
    const int month_offsets[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    const int weekday_year = year - (month < 2 ? 1 : 0);
    date.tm_wday = (weekday_year + weekday_year / 4 - weekday_year / 100 +
                    weekday_year / 400 + month_offsets[month] + date.tm_mday) % 7;
    return true;
}

int main()
{
    const std::time_t current = std::time(nullptr);
    const std::tm *now = std::localtime(&current);
    if (now != nullptr)
    {
        std::cout << "17.37 formatted now: "
                  << std::put_time(now, "%Y-%m-%d %H:%M:%S") << '\n';
    }
    else
    {
        std::cerr << "could not read the current local time\n";
    }

    std::string line;
    std::cout << "17.38/17.39 enter lines like 2026 11 05 (empty line ends):\n";
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            break;
        }
        std::tm parsed = {};
        if (parse_date(line, parsed))
        {
            std::cout << "  parsed: " << std::put_time(&parsed, "%A, %B %d %Y")
                      << '\n';
        }
        else
        {
            std::cout << "  failed to parse\n";
        }
    }
    return 0;
}
