# 第 11 章：关联容器

已核对并整理 11.1–11.38（书页 372–422 / PDF 页 398–448）。知识复习见 [复习提纲](REVIEW.md)。

## 11.1 map 与 vector 的区别

`vector<int>` 用下标（整数位置）访问元素；`map` 的下标可以是任意可作为关键字的类型，元素按关键字组织而不是按位置。`word_counts[some_value]` 在 map 上按关键字查找计数，在 vector 上是第 some_value 个元素。

## 11.2 容器选择

按人名查电话号码用 `map`；统计单词出现次数用 `map<string, size_t>`；只关心单词是否出现过（黑名单）用 `set`；需要保持加入顺序或允许重复用 `vector`/`list`；同一关键字多条记录（作者对应多部作品）用 `multimap`。

## 11.3–11.4 单词计数

[ex11_03_04.cpp](ex11_03_04.cpp) 用 `++counts[word]` 统计：下标运算符在关键字不存在时插入并值初始化为 0。11.4 在计数前先转小写、去掉标点，输入 `Example. example EXAMPLE The the` 输出 `example occurs 3 time(s)` 与 `the occurs 2 time(s)`。转换只处理 ASCII 字符。

## 11.5–11.6 set 与 map、set 与 list

只回答"某单词是否出现"用 `set`：不需要为每个单词维护计数，语义更直接。11.6 要打印"缺失单词列表"：`list` 保留加入顺序、支持重复，`set` 会自动排序去重——若要求按字典序且唯一，`set` 更合适；若要保持输入顺序，`list` 更合适。

## 11.7–11.8 家庭与黑名单

[ex11_07_08.cpp](ex11_07_08.cpp) 用 `map<string, vector<string>>` 保存每个家庭的孩子，`families[family]` 首次访问即创建空条目，所以没有孩子的家庭也会出现。11.8 用 `set<string>` 存放被排除的单词：`find` 在 set 上是对数时间，向量的线性查找在名单变长后明显变慢。

## 11.9 单词的行号列表

[ex11_09.cpp](ex11_09.cpp) 用 `map<string, list<int>>` 记录每个单词出现的行号，逐行 `getline` 后用 `istringstream` 切词。样例两行输出 `first: 1 2`、`line: 1 2`、`second: 2`、`words: 1`。

## 11.10 迭代器作关键字

`map<vector<int>::iterator, int>` 合法：随机访问迭代器提供 `<`。`map<list<int>::iterator, int>` 不合法：双向迭代器没有 `<`，无法维持严格弱序。

## 11.11 比较函数与关键字类型

`bool compareIsbn(const Sales_data &, const Sales_data &)` 加上 `bool (*)(const Sales_data &, const Sales_data &)` 的指针类型，可以作为 map 的第三个模板实参并在构造时传入，替代对 `Sales_data` 定义 `<`。

## 11.12–11.13 pair 的读入与三种插入

[ex11_12_13.cpp](ex11_12_13.cpp) 读入 `姓名 年龄` 对存入 `vector<pair<string, int>>`；11.13 演示 `push_back({"Ann", "Lee"})`、`push_back(make_pair("Bob", "Wu"))`、`emplace_back("Cai", "Xu")` 三种写法，最后把同样的 pair 插入 `map`。三种写法结果一致，`emplace_back` 就地构造最省事。

## 11.14 家庭与生日

[ex11_14.cpp](ex11_14.cpp) 把映射值扩展为 `vector<pair<string, string>>`，每个孩子带出生日期，输出 `Li: Ming (1990-01-01) Xia (1993-05-20)`。

## 11.15–11.19 迭代器与类型成员

`map<int, vector<int>>` 的 `key_type` 是 `int`，`mapped_type` 是 `vector<int>`，`value_type` 是 `pair<const int, vector<int>>`。11.16 中 `auto map_it = m.begin(); map_it->second = ...;` 合法，而给 `map_it->first` 赋值不合法——pair 的关键字部分是 `const`。[ex11_16_17.cpp](ex11_16_17.cpp) 演示改值并输出 `Ann is now 31`。11.18 中迭代器解引用得到 `value_type`，`it->first` 是关键字；11.19 用同样的思路取出 `map<Sales_data, size_t>` 的关键字。11.17 中 set 与 vector 之间的拷贝见同一文件：`vector → set` 用 `inserter`、`set → vector` 用 `back_inserter` 都合法，`back_inserter` 对 set 不合法（没有 `push_back`）。

## 11.20–11.22 insert 的返回值

[ex11_20_21.cpp](ex11_20_21.cpp) 用 `counts.insert({word, 1})` 计数：返回 `pair<iterator, bool>`，`second` 为假说明关键字已存在，此时 `result.first->second` 指向原条目，递增即可；11.21 把同样的逻辑压成 `++(counts.insert({word, 0}).first->second);`。两个版本对同一输入输出一致：`(hello, 3) (primer, 1) (world, 2)`。11.22 问插入 `pair<string, vector<int>>` 的返回类型：对 `map<string, vector<int>>` 是 `pair<map<string, vector<int>>::iterator, bool>`。

## 11.23 家庭版 emplace

`families.emplace(last_name, vector<string>{child})` 在关键字不存在时一次性创建带首孩子的条目；已存在时 emplace 不做任何事，需要再向 `families[last_name]` 追加。该逻辑已并入 [ex11_07_08.cpp](ex11_07_08.cpp) 的家庭数据。

## 11.24–11.26 下标运算

11.24 的 `m["Anna"] = 365`：先插入 `{"Anna", ""}`（默认构造），再赋新值。11.25 的 `v[0] = 42` 对空 vector 是未定义行为——下标不做越界检查，也不会创建元素。11.26 中 `map` 支持下标（访问或插入），`set` 不支持（没有"与关键字关联的值"）；下标要求关键字可默认构造，`at` 则只查找并在找不到时抛出 `out_of_range`。

## 11.27–11.30 find、count 与 equal_range

只想知道关键字是否存在用 `find`；要统计重复次数（multimap/multiset）用 `count`。11.28 中 `find(word)` 返回 `map<string, vector<int>>::iterator`。11.29 的 `equal_range` 返回 `pair<iterator, iterator>`。11.30 的 `pos.first->second` 是匹配范围第一条记录的值，例如作者的第一部作品。

## 11.31–11.32 multimap 的删除与有序遍历

[ex11_31_32.cpp](ex11_31_32.cpp) 用 `find` 定位作者、按 `count` 次调用 `erase(it)` 并使用其返回值继续删除，一次删掉该作者全部作品。multimap 按关键字排序，直接迭代即得到按作者分组、组内按插入顺序的输出，11.32 的"按作者排序打印"因此不需要额外排序。

## 11.33–11.36 单词转换程序

[ex11_33.cpp](ex11_33.cpp) 复现书中程序：`build_map` 从规则文件构造映射，`transform` 用 `find` 查找（11.34：若用下标，未命中的单词会被当作新关键字插入 map，破坏只读语义），每行输出首字母大写。对 [data/transform_rules.txt](data/transform_rules.txt) 与 [data/transform_text.txt](data/transform_text.txt) 输出：

```text
Where are you
Why dont you send me a picture
Okay? thanks later by the way
```

11.35：构造映射改用 `insert` 后，重复关键字的**第一条**规则生效；书中的下标写法是后写的覆盖先写的。11.36：规则行若有多余空格，`getline` 读到的值以空格开头，`substr(1)` 只去掉一个空格，转换结果会带上多余的空白；更稳妥的做法是跳过值前的全部空白。

## 11.37–11.38 无序容器

无序容器平均常数时间的查找换来元素无序与自定义哈希的要求；关键字类型不提供 `<` 时也能使用。当必须按序输出或遍历、或哈希函数质量差导致桶退化时，有序版本更好。[ex11_38.cpp](ex11_38.cpp) 把单词计数与转换程序换到 `unordered_map`：计数条目按桶序输出（`world` 在 `hello` 之前），转换结果与有序版本完全相同。

## 验证记录

本轮 10 个程序使用 MSVC 19.29（VS2019 BuildTools，14.29.30133）、`/std:c++17`、`/W4` 编译，单词计数、家庭映射、pair 插入、insert 返回值、multimap 删除与两套转换程序均按上述样例运行核对。个人复习完成后再勾选 [复习提纲](REVIEW.md) 中的检查项。
