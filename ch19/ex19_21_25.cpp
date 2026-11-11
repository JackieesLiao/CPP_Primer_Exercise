#include <iostream>
#include <new>
#include <string>
#include <utility>

// 19.21-19.25: a Token built on an anonymous union. A discriminant
// records which member is alive; the copy constructor, assignment
// operators and destructor switch on that tag so the std::string member
// is constructed, copied or destroyed exactly when it is active.

class Token
{
public:
    Token() : token_type(INT), ival(0)
    {
    }

    Token(char value) : token_type(CHAR), cval(value)
    {
    }

    Token(int value) : token_type(INT), ival(value)
    {
    }

    Token(double value) : token_type(DOUBLE), dval(value)
    {
    }

    Token(const std::string &value) : token_type(STRING)
    {
        new (&sval) std::string(value);
    }

    Token(const Token &other);
    Token &operator=(const Token &other);
    ~Token();

    Token &operator=(char value);
    Token &operator=(int value);
    Token &operator=(double value);
    Token &operator=(const std::string &value);

    std::string as_string() const
    {
        switch (token_type)
        {
        case CHAR:
            return std::string(1, cval);
        case INT:
            return std::to_string(ival);
        case DOUBLE:
            return std::to_string(dval);
        case STRING:
            return sval;
        default:
            return std::string();
        }
    }

private:
    enum Type
    {
        CHAR,
        INT,
        DOUBLE,
        STRING
    };

    void copy_union(const Token &other);
    void destroy_union();

    Type token_type;
    union
    {
        char cval;
        int ival;
        double dval;
        std::string sval;
    };
};

inline void Token::copy_union(const Token &other)
{
    switch (other.token_type)
    {
    case CHAR:
        cval = other.cval;
        break;
    case INT:
        ival = other.ival;
        break;
    case DOUBLE:
        dval = other.dval;
        break;
    case STRING:
        new (&sval) std::string(other.sval);
        break;
    default:
        break;
    }
}

inline void Token::destroy_union()
{
    if (token_type == STRING)
    {
        sval.~basic_string();
    }
}

inline Token::Token(const Token &other) : token_type(other.token_type)
{
    copy_union(other);
}

inline Token &Token::operator=(const Token &other)
{
    if (this != &other)
    {
        if (other.token_type == STRING)
        {
            return *this = other.sval;
        }

        destroy_union();
        copy_union(other);
        token_type = other.token_type;
    }
    return *this;
}

inline Token::~Token()
{
    destroy_union();
}

inline Token &Token::operator=(char value)
{
    destroy_union();
    cval = value;
    token_type = CHAR;
    return *this;
}

inline Token &Token::operator=(int value)
{
    destroy_union();
    ival = value;
    token_type = INT;
    return *this;
}

inline Token &Token::operator=(double value)
{
    destroy_union();
    dval = value;
    token_type = DOUBLE;
    return *this;
}

inline Token &Token::operator=(const std::string &value)
{
    if (token_type == STRING)
    {
        sval = value;
    }
    else
    {
        // Copy before reusing the union storage, so failure preserves the old value.
        std::string prepared(value);
        new (&sval) std::string(std::move(prepared));
        token_type = STRING;
    }
    return *this;
}

int main()
{
    Token a(42);
    Token b(std::string("text"));
    Token copied(b);
    std::cout << "copied holds: " << copied.as_string() << '\n';

    copied = a;
    std::cout << "after int assignment: " << copied.as_string() << '\n';
    copied = 3.14;
    std::cout << "after double assignment: " << copied.as_string() << '\n';
    copied = std::string("back to string");
    std::cout << "after string assignment: " << copied.as_string() << '\n';
    return 0;
}
