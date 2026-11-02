#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string replace_with_iterators(std::string text, const std::string &old_value,
                                   const std::string &new_value)
{
    if (old_value.empty())
    {
        throw std::invalid_argument("The search string must not be empty.");
    }
    auto position = text.begin();
    while (static_cast<std::size_t>(text.end() - position) >= old_value.size())
    {
        if (std::equal(old_value.begin(), old_value.end(), position))
        {
            position = text.erase(position, position + old_value.size());
            position = text.insert(position, new_value.begin(), new_value.end());
            position += new_value.size();
        }
        else
        {
            ++position;
        }
    }
    return text;
}

std::string replace_with_positions(std::string text, const std::string &old_value,
                                   const std::string &new_value)
{
    if (old_value.empty())
    {
        throw std::invalid_argument("The search string must not be empty.");
    }
    std::string::size_type position = 0;
    while ((position = text.find(old_value, position)) != std::string::npos)
    {
        text.replace(position, old_value.size(), new_value);
        position += new_value.size();
    }
    return text;
}

std::string with_affixes(std::string name, const std::string &prefix, const std::string &suffix)
{
    name.insert(name.begin(), prefix.begin(), prefix.end());
    name.append(suffix);
    return name;
}

std::string with_affixes_by_position(std::string name, const std::string &prefix,
                                     const std::string &suffix)
{
    name.insert(0, prefix);
    name.insert(name.size(), suffix);
    return name;
}

void print_matches(const std::string &text, const std::string &characters, bool invert)
{
    std::string::size_type position = 0;
    while (position < text.size())
    {
        if (invert)
        {
            position = text.find_first_not_of(characters, position);
        }
        else
        {
            position = text.find_first_of(characters, position);
        }
        if (position == std::string::npos)
        {
            break;
        }
        std::cout << text[position];
        ++position;
    }
    std::cout << '\n';
}

int main()
{
    const std::vector<char> letters{'h', 'i'};
    const std::string converted(letters.begin(), letters.end());
    std::cout << converted << '\n';

    const std::string sample = "tho thru";
    std::cout << replace_with_iterators(sample, "tho", "though") << '\n';
    std::cout << replace_with_positions(sample, "thru", "through") << '\n';
    std::cout << with_affixes("Ada", "Ms. ", " Jr.") << '\n';
    std::cout << with_affixes_by_position("Ada", "Ms. ", " Jr.") << '\n';

    const std::string mixed = "ab2c3d7R4E6";
    const std::string digits = "0123456789";
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    print_matches(mixed, digits, false);
    print_matches(mixed, alphabet, false);
    print_matches(mixed, alphabet, true);
    print_matches(mixed, digits, true);

    const std::vector<std::string> numbers{"1", "2", "3"};
    int integer_sum = 0;
    double floating_sum = 0.0;
    for (const std::string &number : numbers)
    {
        integer_sum += std::stoi(number);
        floating_sum += std::stod(number);
    }
    std::cout << integer_sum << ' ' << floating_sum << '\n';
    return 0;
}
