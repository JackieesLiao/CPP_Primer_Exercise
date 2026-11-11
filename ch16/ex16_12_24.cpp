#include <iostream>
#include <list>
#include <string>

#include "Blob.h"

// 16.12/16.24/16.58: Blob<int> and Blob<string>, the iterator-range
// constructor, BlobPtr traversal and the variadic emplace_back.

int main()
{
    Blob<int> numbers{1, 2, 3};
    numbers.push_back(4);
    std::cout << "Blob<int>: front " << numbers.front() << ", back "
              << numbers.back() << ", size " << numbers.size() << '\n';

    const std::list<std::string> words{"alpha", "beta", "gamma"};
    Blob<std::string> from_range(words.cbegin(), words.cend());
    std::cout << "Blob<string> from iterator range:";
    for (BlobPtr<std::string> it = from_range.begin(); it != from_range.end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';

    from_range.emplace_back("delta");
    std::cout << "after emplace_back: back is " << from_range.back() << '\n';
    return 0;
}
