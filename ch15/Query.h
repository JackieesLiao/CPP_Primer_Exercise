#ifndef CH15_QUERY_H
#define CH15_QUERY_H

#include <algorithm>
#include <memory>
#include <set>
#include <string>

#include "TextQuery.h"

// 15.9/15.31/15.35/15.39-15.41: the query language. Query wraps a
// Query_base through shared_ptr; the operators build NotQuery, OrQuery and
// AndQuery trees; every node evaluates against a TextQuery.

class Query;

class Query_base
{
    friend class Query;

protected:
    using LineNo = TextQuery::LineNo;

    virtual ~Query_base() = default;

private:
    virtual QueryResult eval(const TextQuery &text) const = 0;
    virtual std::string rep() const = 0;
};

class Query
{
    friend Query operator~(const Query &operand);
    friend Query operator|(const Query &left, const Query &right);
    friend Query operator&(const Query &left, const Query &right);

public:
    Query(const std::string &word);

    QueryResult eval(const TextQuery &text) const
    {
        return q->eval(text);
    }

    std::string rep() const
    {
        return q->rep();
    }

private:
    Query(std::shared_ptr<Query_base> query) : q(query)
    {
    }

    std::shared_ptr<Query_base> q;
};

class WordQuery : public Query_base
{
    friend class Query;

    explicit WordQuery(const std::string &searched) : word(searched)
    {
    }

    QueryResult eval(const TextQuery &text) const
    {
        return text.query(word);
    }

    std::string rep() const
    {
        return word;
    }

    std::string word;
};

inline Query::Query(const std::string &word)
    : q(new WordQuery(word))
{
}

class NotQuery : public Query_base
{
    friend Query operator~(const Query &operand);

    explicit NotQuery(const Query &operand) : query(operand)
    {
    }

    QueryResult eval(const TextQuery &text) const;
    std::string rep() const
    {
        return "~(" + query.rep() + ")";
    }

    Query query;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

inline QueryResult NotQuery::eval(const TextQuery &text) const
{
    const QueryResult matched = query.eval(text);
    auto no_match_lines = std::make_shared<std::set<LineNo>>();
    for (std::size_t number = 0; number < matched.get_file()->size(); ++number)
    {
        if (std::find(matched.begin(), matched.end(), number) == matched.end())
        {
            no_match_lines->insert(number);
        }
    }
    return QueryResult(rep(), no_match_lines, matched.get_file());
}

class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query &left_operand, const Query &right_operand,
                std::string symbol)
        : lhs(left_operand), rhs(right_operand), op_sym(symbol)
                {
                }

    std::string rep() const
    {
        return "(" + lhs.rep() + " " + op_sym + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;
    std::string op_sym;
};

class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query &left, const Query &right);

    OrQuery(const Query &left_operand, const Query &right_operand)
        : BinaryQuery(left_operand, right_operand, "|")
    {
    }

    QueryResult eval(const TextQuery &text) const
    {
        const QueryResult left_result = lhs.eval(text);
        const QueryResult right_result = rhs.eval(text);
        auto combined = std::make_shared<std::set<LineNo>>(left_result.begin(),
                                                           left_result.end());
        combined->insert(right_result.begin(), right_result.end());
        return QueryResult(rep(), combined, left_result.get_file());
    }
};

inline Query operator|(const Query &left, const Query &right)
{
    return std::shared_ptr<Query_base>(new OrQuery(left, right));
}

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query &left, const Query &right);

    AndQuery(const Query &left_operand, const Query &right_operand)
        : BinaryQuery(left_operand, right_operand, "&")
    {
    }

    QueryResult eval(const TextQuery &text) const
    {
        const QueryResult left_result = lhs.eval(text);
        const QueryResult right_result = rhs.eval(text);
        auto both = std::make_shared<std::set<LineNo>>();
        std::set_intersection(left_result.begin(), left_result.end(),
                              right_result.begin(), right_result.end(),
                              std::inserter(*both, both->begin()));
        return QueryResult(rep(), both, left_result.get_file());
    }
};

inline Query operator&(const Query &left, const Query &right)
{
    return std::shared_ptr<Query_base>(new AndQuery(left, right));
}
#endif
