#include <iostream>
#include <vector>

#include "String.h"

// 13.44/13.47/13.48: our String in action. Assignments and copies print
// traces; pushing into a vector<String> shows reallocation moving the
// existing elements (13.48/13.50): capacity 1 -> 2 moves one element,
// 2 -> 4 moves two.

int main()
{
    const String source("primer");
    std::cout << "source is " << source.c_str() << " (" << source.size()
              << " chars)\n";

    String copied(source);
    String assigned;
    assigned = source;
    assigned = String("moved in");
    std::cout << "assigned now holds " << assigned.c_str() << '\n';

    std::vector<String> words;
    std::cout << "--- growth from 0 to 1\n";
    words.push_back(String("one"));
    std::cout << "--- growth from 1 to 2\n";
    words.push_back(String("two"));
    std::cout << "--- growth from 2 to 4\n";
    words.push_back(String("three"));
    words.push_back(String("four"));
    std::cout << "words: ";
    for (const String &word : words)
    {
        std::cout << word.c_str() << ' ';
    }
    std::cout << '\n';
    return 0;
}
