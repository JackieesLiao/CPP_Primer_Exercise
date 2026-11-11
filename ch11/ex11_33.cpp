#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

// 11.33: the book's word transformation program. A rules file maps
// abbreviations to their replacements; each line of the text file is
// transformed and printed with its first letter capitalized.

std::map<std::string, std::string> build_map(std::ifstream &rules)
{
    std::map<std::string, std::string> trans_map;
    std::string key, value;
    while (rules >> key && std::getline(rules, value))
    {
        if (value.size() > 1)
        {
            // 11.35: insert keeps the first rule for a repeated key; the
            // book's subscript version lets a later rule overwrite it.
            trans_map.insert({key, value.substr(1)});
        }
        else
        {
            throw std::runtime_error("no rule for " + key);
        }
    }
    return trans_map;
}

const std::string &transform(const std::string &word,
                             const std::map<std::string, std::string> &trans_map)
{
    auto it = trans_map.find(word);
    if (it != trans_map.cend())
    {
        return it->second;
    }
    return word;
}

void word_transform(std::ifstream &rules, std::ifstream &text)
{
    const std::map<std::string, std::string> trans_map = build_map(rules);
    std::string line;
    while (std::getline(text, line))
    {
        std::istringstream stream(line);
        std::string output, word;
        bool first_word = true;
        while (stream >> word)
        {
            if (first_word)
            {
                first_word = false;
            }
            else
            {
                output += ' ';
            }
            output += transform(word, trans_map);
        }
        if (!output.empty())
        {
            output[0] = static_cast<char>(
                std::toupper(static_cast<unsigned char>(output[0])));
        }
        std::cout << output << '\n';
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: ex11_33 rulesfile textfile\n";
        return 1;
    }
    std::ifstream rules(argv[1]);
    if (!rules)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }
    std::ifstream text(argv[2]);
    if (!text)
    {
        std::cerr << "Cannot open " << argv[2] << '\n';
        return 1;
    }
    word_transform(rules, text);
    return 0;
}
