#ifndef CH12_STRBLOB_TEXT_QUERY_H
#define CH12_STRBLOB_TEXT_QUERY_H

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "StrBlob.h"

// 12.32: the text query of TextQuery.h, but the file lives in a StrBlob
// and results hand out ConstStrBlobPtr iterators instead of exposing the
// vector directly.

class StrBlobQueryResult;

class StrBlobTextQuery
{
public:
    using LineNo = std::vector<std::string>::size_type;

    explicit StrBlobTextQuery(std::ifstream &input)
    {
        std::string text;
        while (std::getline(input, text))
        {
            lines.push_back(text);
            const LineNo number = lines.size() - 1;
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

    StrBlobQueryResult query(const std::string &searched) const;

private:
    StrBlob lines;
    std::map<std::string, std::shared_ptr<std::set<LineNo>>> occurrences;
};

class StrBlobQueryResult
{
    friend std::ostream &print(std::ostream &output,
                               const StrBlobQueryResult &result);

public:
    StrBlobQueryResult(const std::string &searched,
                       std::shared_ptr<std::set<StrBlobTextQuery::LineNo>> numbers,
                       const StrBlob &text)
        : word(searched), numbers(numbers), lines(text)
                       {
                       }

    ConstStrBlobPtr begin() const
    {
        return lines.cbegin();
    }

    ConstStrBlobPtr end() const
    {
        return lines.cend();
    }

private:
    std::string word;
    std::shared_ptr<std::set<StrBlobTextQuery::LineNo>> numbers;
    StrBlob lines;
};

inline StrBlobQueryResult StrBlobTextQuery::query(const std::string &searched) const
{
    static const std::shared_ptr<std::set<LineNo>> no_result(new std::set<LineNo>);
    auto found = occurrences.find(searched);
    if (found == occurrences.cend())
    {
        return StrBlobQueryResult(searched, no_result, lines);
    }
    return StrBlobQueryResult(searched, found->second, lines);
}

inline std::ostream &print(std::ostream &output, const StrBlobQueryResult &result)
{
    output << result.word << " occurs " << result.numbers->size() << " time(s)"
           << '\n';
    for (const StrBlobTextQuery::LineNo number : *result.numbers)
    {
        ConstStrBlobPtr line_it = result.begin();
        for (StrBlobTextQuery::LineNo index = 0; index < number; ++index)
        {
            line_it.increment();
        }
        output << "  (line " << number + 1 << ") " << line_it.deref() << '\n';
    }
    return output;
}
#endif
