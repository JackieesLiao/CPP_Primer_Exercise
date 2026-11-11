#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// 11.38: the word count of 11.3 and the transformation program of 11.33
// again, this time on unordered_map. The word count prints entries in
// bucket order instead of alphabetical order; the transformation result
// does not depend on the container's order at all.

std::unordered_map<std::string, std::size_t> word_count(const std::vector<std::string> &words)
{
    std::unordered_map<std::string, std::size_t> counts;
    for (const std::string &word : words)
    {
        ++counts[word];
    }
    return counts;
}

std::unordered_map<std::string, std::string> build_map(std::ifstream &rules)
{
    std::unordered_map<std::string, std::string> trans_map;
    std::string key, value;
    while (rules >> key && std::getline(rules, value))
    {
        if (value.size() > 1)
        {
            trans_map.insert({key, value.substr(1)});
        }
    }
    return trans_map;
}

const std::string &transform(const std::string &word,
                             const std::unordered_map<std::string, std::string> &trans_map)
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
    const std::unordered_map<std::string, std::string> trans_map = build_map(rules);
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
    const std::vector<std::string> sample{"hello", "world", "hello", "primer",
                                          "world", "hello"};
    const std::unordered_map<std::string, std::size_t> counts = word_count(sample);
    std::cout << "11.3 word count in bucket order:\n";
    for (const auto &entry : counts)
    {
        std::cout << "  " << entry.first << " occurs " << entry.second
                  << " time(s)\n";
    }

    if (argc < 3)
    {
        std::cerr << "Pass a rules file and a text file to run the "
                     "transformation as well.\n";
        return 0;
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
