#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// 17.21/17.22/17.23/17.24: phone-number validation and reformatting.
// The separator group captures a hyphen, dot, space or empty string.
// Its backreference requires both separators to match.

const std::regex &phone_pattern()
{
    static const std::regex pattern("(\\d{3})([-. ]?)(\\d{3})\\2(\\d{4})");
    return pattern;
}

std::string reformat(const std::string &phone)
{
    static const std::string format = "($1) $3-$4";
    return std::regex_replace(phone, phone_pattern(), format);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ex17_21_22_24 phonesfile\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }
    std::string line;
    // Try a whole space-separated number before falling back to a single token.
    const std::regex phone_field(R"(\d{3} \d{3} \d{4}(?=\s|$)|\S+)");
    while (std::getline(input, line))
    {
        std::istringstream stream(line);
        std::string name;
        if (!(stream >> name))
        {
            continue;
        }
        std::string fields;
        std::getline(stream, fields);

        std::vector<std::string> valid;
        const std::sregex_iterator end;
        for (std::sregex_iterator field(fields.cbegin(), fields.cend(), phone_field);
             field != end; ++field)
        {
            const std::string phone = field->str();
            if (std::regex_match(phone, phone_pattern()))
            {
                valid.push_back(reformat(phone));
            }
            else
            {
                std::cout << "invalid number " << phone << " for " << name << '\n';
            }
        }
        std::cout << name << ":";
        for (const std::string &formatted : valid)
        {
            std::cout << ' ' << formatted;
        }
        std::cout << '\n';
    }
    return 0;
}
