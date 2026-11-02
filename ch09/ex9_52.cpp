#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

double calculate(double left, char operation, double right)
{
    double result = 0.0;
    switch (operation)
    {
    case '+':
        result = left + right;
        break;
    case '-':
        result = left - right;
        break;
    case '*':
        result = left * right;
        break;
    case '/':
        if (right == 0.0)
        {
            throw std::invalid_argument("Division by zero.");
        }
        result = left / right;
        break;
    default:
        throw std::invalid_argument("Unknown operator.");
    }
    if (!std::isfinite(result))
    {
        throw std::overflow_error("Non-finite result.");
    }
    return result;
}

std::string pop_token(std::stack<std::string> &tokens)
{
    if (tokens.empty())
    {
        throw std::invalid_argument("Incomplete expression.");
    }
    std::string value = tokens.top();
    tokens.pop();
    return value;
}

double parse_number(const std::string &token)
{
    std::size_t parsed = 0;
    double value = std::stod(token, &parsed);
    if (parsed != token.size() || !std::isfinite(value))
    {
        throw std::invalid_argument("Invalid number.");
    }
    return value;
}

double evaluate(const std::string &expression)
{
    std::stack<std::string> tokens;
    for (std::size_t index = 0; index < expression.size();)
    {
        const char character = expression[index];
        if (character == ' ' || character == '\t')
        {
            ++index;
        }
        else if (character >= '0' && character <= '9')
        {
            std::size_t end = index + 1;
            while (end < expression.size() && expression[end] >= '0' && expression[end] <= '9')
            {
                ++end;
            }
            tokens.push(expression.substr(index, end - index));
            index = end;
        }
        else if (character == '(' || character == '+' || character == '-' || character == '*' ||
                 character == '/')
        {
            tokens.push(std::string(1, character));
            ++index;
        }
        else if (character == ')')
        {
            const double right = parse_number(pop_token(tokens));
            const std::string operation = pop_token(tokens);
            const double left = parse_number(pop_token(tokens));
            if (operation.size() != 1 || pop_token(tokens) != "(")
            {
                throw std::invalid_argument("Expected a parenthesized binary expression.");
            }
            std::ostringstream result;
            result << std::setprecision(std::numeric_limits<double>::max_digits10)
                   << calculate(left, operation[0], right);
            tokens.push(result.str());
            ++index;
        }
        else
        {
            throw std::invalid_argument("Unexpected character.");
        }
    }
    const double result = parse_number(pop_token(tokens));
    if (!tokens.empty())
    {
        throw std::invalid_argument("Unmatched tokens remain.");
    }
    return result;
}

int main()
{
    std::string expression;
    if (!std::getline(std::cin, expression))
    {
        std::cerr << "Expected an expression.\n";
        return 1;
    }
    try
    {
        std::cout << evaluate(expression) << '\n';
    }
    catch (const std::exception &error)
    {
        std::cerr << "Invalid expression: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
