#include <iostream>

// 2.8: print 2M followed by a newline with escape sequences.
// \x4d is the hexadecimal escape for 'M', \012 the octal escape for '\n'.
// The backslash after \x4d ends the hex escape, so no extra digits are read.

int main()
{
    std::cout << "2\x4d\012";
    return 0;
}
