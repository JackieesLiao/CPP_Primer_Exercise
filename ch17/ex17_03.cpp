#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <tuple>

#include "../ch13/StrVec.h"

// 17.3: the query function of the 13.42 TextQuery rewritten with tuple.
// The result is (word, line-number set, shared lines) instead of a class.

class TupleTextQuery
{
public:
    using LineNo = std::size_t;
    using Result = std::tuple<std::string, std::shared_ptr<std::set<LineNo>>,
                              std::shared_ptr<StrVec>>;

    explicit TupleTextQuery(std::ifstream &input) : lines(new StrVec)
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

    Result query(const std::string &searched) const
    {
        static const std::shared_ptr<std::set<LineNo>> no_result(new std::set<LineNo>);
        auto found = occurrences.find(searched);
        if (found == occurrences.cend())
        {
            return Result(searched, no_result, lines);
        }
        return Result(searched, found->second, lines);
    }

private:
    std::shared_ptr<StrVec> lines;
    std::map<std::string, std::shared_ptr<std::set<LineNo>>> occurrences;
};

std::ostream &print(std::ostream &output, const TupleTextQuery::Result &result)
{
    output << std::get<0>(result) << " occurs " << std::get<1>(result)->size()
           << " time(s)" << '\n';
    const std::shared_ptr<StrVec> &lines = std::get<2>(result);
    for (const TupleTextQuery::LineNo number : *std::get<1>(result))
    {
        output << "  (line " << number + 1 << ") "
               << *(lines->begin() + number) << '\n';
    }
    return output;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ex17_03 textfile\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open " << argv[1] << '\n';
        return 1;
    }
    const TupleTextQuery document(input);
    print(std::cout, document.query("CMake")) << '\n';
    print(std::cout, document.query("missing")) << '\n';
    return 0;
}
