#include <iostream>
#include <map>
#include <string>

// 11.31: erase every work of one author from a multimap by walking the
// range returned by find and using the iterator erase returns.
// 11.32: the multimap orders its keys, so a plain iteration already prints
// the entries grouped by author in dictionary order.

void erase_author(std::multimap<std::string, std::string> &works,
                  const std::string &author)
{
    std::size_t remaining = works.count(author);
    auto it = works.find(author);
    while (remaining != 0)
    {
        it = works.erase(it);
        --remaining;
    }
}

int main()
{
    std::multimap<std::string, std::string> works{
        {"Shen Congwen", "Biancheng"},
        {"Lu Xun", "Kuangren Riji"},
        {"Bing Xin", "Fanxing"},
        {"Lu Xun", "Ah Q Zhengzhuan"}};
    std::cout << "before erase:\n";
    for (const auto &entry : works)
    {
        std::cout << "  " << entry.first << " - " << entry.second << '\n';
    }
    erase_author(works, "Lu Xun");
    std::cout << "after erasing Lu Xun:\n";
    for (const auto &entry : works)
    {
        std::cout << "  " << entry.first << " - " << entry.second << '\n';
    }
    return 0;
}
