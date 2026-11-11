#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// 17.1: a tuple standing in for the sales_data members of the book's
// code: ISBN count and price. 17.2: the tuple from the text query
// example: word, list of words and a pair.

int main()
{
    std::tuple<std::string, int, double> sale{"0-201-70353-X", 4, 99.96};
    std::cout << "sale: " << std::get<0>(sale) << ' ' << std::get<1>(sale)
              << ' ' << std::get<2>(sale) << '\n';

    std::tuple<std::string, std::vector<std::string>,
               std::pair<std::string, int>>
        query{"CMake", {"build", "file"}, {"line", 1}};
    std::cout << "query: " << std::get<0>(query) << ", " << std::get<1>(query).size()
              << " words, pair " << std::get<2>(query).first << ' '
              << std::get<2>(query).second << '\n';
    return 0;
}
