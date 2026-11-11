#ifndef CH13_STRVEC_TEXT_QUERY_H
#define CH13_STRVEC_TEXT_QUERY_H

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "StrVec.h"

// 13.42: the text query of chapter 12, now storing the file in StrVec and
// sharing it with QueryResult through a shared_ptr.

class StrVecQueryResult;

class StrVecTextQuery
{
public:
    using LineNo = std::size_t;

    explicit StrVecTextQuery(std::ifstream &input) : lines(new StrVec)
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

    StrVecQueryResult query(const std::string &searched) const;

private:
    std::shared_ptr<StrVec> lines;
    std::map<std::string, std::shared_ptr<std::set<LineNo>>> occurrences;
};

class StrVecQueryResult
{
    friend std::ostream &print(std::ostream &output,
                               const StrVecQueryResult &result);

public:
    StrVecQueryResult(const std::string &searched,
                      std::shared_ptr<std::set<StrVecTextQuery::LineNo>> numbers,
                      std::shared_ptr<StrVec> text)
        : word(searched), numbers(numbers), lines(text)
                      {
                      }

private:
    std::string word;
    std::shared_ptr<std::set<StrVecTextQuery::LineNo>> numbers;
    std::shared_ptr<StrVec> lines;
};

inline StrVecQueryResult StrVecTextQuery::query(const std::string &searched) const
{
    static const std::shared_ptr<std::set<LineNo>> no_result(new std::set<LineNo>);
    auto found = occurrences.find(searched);
    if (found == occurrences.cend())
    {
        return StrVecQueryResult(searched, no_result, lines);
    }
    return StrVecQueryResult(searched, found->second, lines);
}

inline std::ostream &print(std::ostream &output, const StrVecQueryResult &result)
{
    output << result.word << " occurs " << result.numbers->size() << " time(s)"
           << '\n';
    for (const StrVecTextQuery::LineNo number : *result.numbers)
    {
        output << "  (line " << number + 1 << ") "
               << *(result.lines->begin() + number) << '\n';
    }
    return output;
}
#endif
