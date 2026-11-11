#ifndef CH15_TEXT_QUERY_H
#define CH15_TEXT_QUERY_H

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// The chapter-12 text query, extended for chapter 15: QueryResult exposes
// begin/end over the matching line numbers and get_file for the text, the
// pieces the Query classes of 15.9 need to evaluate.

class QueryResult;

class TextQuery
{
public:
    using LineNo = std::vector<std::string>::size_type;

    explicit TextQuery(std::ifstream &input) : lines(new std::vector<std::string>)
    {
        std::string text;
        while (std::getline(input, text))
        {
            lines->push_back(text);
            const LineNo number = lines->size() - 1;
            std::istringstream stream(text);
            std::string word;
            while (stream >> word)
            {
                std::shared_ptr<std::set<LineNo>> &entry = occurrences[word];
                if (!entry)
                {
                    entry.reset(new std::set<LineNo>);
                }
                entry->insert(number);
            }
        }
    }

    QueryResult query(const std::string &searched) const;

private:
    std::shared_ptr<std::vector<std::string>> lines;
    std::map<std::string, std::shared_ptr<std::set<LineNo>>> occurrences;
};

class QueryResult
{
    friend std::ostream &print(std::ostream &output, const QueryResult &result);

public:
    using LineNo = TextQuery::LineNo;

    QueryResult(const std::string &searched,
                std::shared_ptr<std::set<TextQuery::LineNo>> numbers,
                std::shared_ptr<std::vector<std::string>> text)
        : word(searched), numbers(numbers), lines(text)
                {
                }

    std::set<TextQuery::LineNo>::const_iterator begin() const
    {
        return numbers->cbegin();
    }

    std::set<TextQuery::LineNo>::const_iterator end() const
    {
        return numbers->cend();
    }

    std::shared_ptr<std::vector<std::string>> get_file() const
    {
        return lines;
    }

private:
    std::string word;
    std::shared_ptr<std::set<TextQuery::LineNo>> numbers;
    std::shared_ptr<std::vector<std::string>> lines;
};

inline QueryResult TextQuery::query(const std::string &searched) const
{
    static const std::shared_ptr<std::set<LineNo>> no_result(new std::set<LineNo>);
    auto found = occurrences.find(searched);
    if (found == occurrences.cend())
    {
        return QueryResult(searched, no_result, lines);
    }
    return QueryResult(searched, found->second, lines);
}

inline std::ostream &print(std::ostream &output, const QueryResult &result)
{
    output << result.word << " occurs " << result.numbers->size() << " time(s)"
           << '\n';
    for (const TextQuery::LineNo number : *result.numbers)
    {
        output << "  (line " << number + 1 << ") " << (*result.lines)[number]
               << '\n';
    }
    return output;
}
#endif
