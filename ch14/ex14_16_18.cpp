#include <iostream>
#include <string>

#include "../ch12/StrBlob.h"

// 14.16/14.18: equality and ordering for StrBlob, StrBlobPtr and StrVec.
// StrBlob compares the underlying vectors; StrBlobPtr compares the vector
// contents first and the position second.

#include "../ch13/StrVec.h"

bool operator==(const StrVec &left, const StrVec &right)
{
    if (left.size() != right.size())
    {
        return false;
    }
    for (std::size_t index = 0; index < left.size(); ++index)
    {
        if (left[index] != right[index])
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const StrVec &left, const StrVec &right)
{
    return !(left == right);
}

bool operator<(const StrVec &left, const StrVec &right)
{
    const std::size_t shorter = left.size() < right.size() ? left.size() : right.size();
    for (std::size_t index = 0; index < shorter; ++index)
    {
        if (left[index] != right[index])
        {
            return left[index] < right[index];
        }
    }
    return left.size() < right.size();
}

int main()
{
    const StrBlob first{"a", "b"};
    const StrBlob second{"a", "b"};
    const StrBlob larger{"a", "c"};
    std::cout << "StrBlob == " << (first == second) << ", != "
              << (first != second) << ", first < larger: " << (first < larger)
              << '\n';

    StrBlob blob{"alpha", "beta", "gamma"};
    StrBlobPtr begin_it = blob.begin();
    StrBlobPtr middle_it = begin_it + 1;
    std::cout << "StrBlobPtr *middle: " << *middle_it << ", ++: " << *++begin_it
              << '\n';
    std::cout << "StrBlobPtr --: " << *(--begin_it) << ", [1]: " << begin_it[1]
              << '\n';
    std::cout << "StrBlobPtr < : " << (begin_it < middle_it) << '\n';

    StrVec vec_a{"alpha", "beta"};
    StrVec vec_b{"alpha", "beta"};
    StrVec vec_c{"alpha", "beta", "gamma"};
    std::cout << "StrVec == " << (vec_a == vec_b) << ", vec_a < vec_c: "
              << (vec_a < vec_c) << '\n';
    return 0;
}
