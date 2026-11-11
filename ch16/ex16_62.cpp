#include <iostream>
#include <string>
#include <unordered_set>

#include "../ch14/Sales_data.h"

// 16.62: specialize std::hash for Sales_data and store the objects in an
// unordered_multiset, where equality and hashing both matter.

namespace std
{
template <>
struct hash<Sales_data>
{
    typedef std::size_t result_type;
    typedef Sales_data argument_type;

    std::size_t operator()(const Sales_data &item) const
    {
        // The ch14 class does not befriend std::hash, so the hash uses the
        // public interface only; a production version would cover every
        // member (or declare the specialization a friend).
        return hash<std::string>()(item.isbn()) ^ hash<double>()(item.avg_price());
    }
};
}  // namespace std

int main()
{
    std::unordered_multiset<Sales_data> store;
    const Sales_data first("0-201-70353-X", 4, 24.99);
    const Sales_data second("0-201-78345-X", 3, 20.0);
    store.insert(first);
    store.insert(first);
    store.insert(second);
    std::cout << "bucket count: " << store.bucket_count()
              << ", first ISBN copies: " << store.count(first)
              << ", total: " << store.size() << '\n';
    return 0;
}
