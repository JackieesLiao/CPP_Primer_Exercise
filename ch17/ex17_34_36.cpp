#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// 17.34/17.35/17.36: conversions between numeric types and strings.
// 17.35 asks for uppercase scientific notation via setf; 17.36 prints
// every string the conversions generate.

std::string as_string(double value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

std::string as_scientific(double value)
{
    std::ostringstream stream;
    stream << std::uppercase << std::scientific << value;
    return stream.str();
}

int main()
{
    const int whole = 42;
    const float half = 0.5f;
    const double pi = 3.14159265358979;
    std::cout << "17.34 int " << std::to_string(whole) << ", float "
              << as_string(half) << ", double " << as_string(pi) << '\n';
    std::cout << "17.35 scientific: " << as_scientific(pi) << '\n';
    std::cout << "17.36 all strings: " << std::to_string(whole) << ' '
              << as_string(half) << ' ' << as_string(pi) << ' '
              << as_scientific(pi) << '\n';
    return 0;
}
