# 第 9 章：顺序容器（整理中）

已核对并整理 9.1–9.13（书页 294–302 / PDF 页 320–328）；后续题目尚未整理。知识复习见 [复习提纲](REVIEW.md)。

## 9.1 选择容器

| 场景 | 建议 | 原因 |
| --- | --- | --- |
| 固定数量的单词逐个插入并保持字典序 | `list` 是合理选择 | 定位插入点仍需线性查找，但找到位置后插入不移动其他元素；数量小或缓存局部性重要时 `vector` 也可能更快，需测量。 |
| 尾部插入、头部删除 | `deque` | 两端操作高效，不需要 `vector` 头部删除时移动后续元素。 |
| 读取未知数量整数，排序后打印 | `vector` | 尾部追加方便，支持随机访问和 `std::sort`，连续存储通常有较好的局部性。 |

固定数量并不意味着必须选 `array`：本题明确比较 `vector`、`deque` 和 `list`，且按顺序插入可能需要改变当前元素数量。

## 9.2 嵌套容器

`std::list<std::deque<int>> values;` 定义一个 list，其元素各自是 `deque<int>`。需要包含 `<list>` 和 `<deque>`。

## 9.3 迭代器范围的约束

两个迭代器必须指向同一容器的元素或尾后位置，并且可以从第一个通过有限次递增到达第二个。范围是左闭右开 `[first, last)`；相等表示空范围，尾后迭代器不能解引用。

## 9.4–9.5 搜索范围

[ex9_04_05.cpp](ex9_04_05.cpp) 分别提供返回 `bool` 的 `contains` 和返回迭代器的 `find_value`。未找到时返回传入的 `last`；调用者必须先比较再解引用。程序的示例容器是 `2 4 6`。

## 9.6 list 迭代器比较

`list` 迭代器是双向迭代器，不提供 `<`。应使用 `iter1 != iter2`，并确保循环体在有效范围内推进迭代器。它们之间可以递增到达的前提不可省略。

## 9.7–9.8 容器类型成员

索引 `vector<int>` 元素使用 `vector<int>::size_type`。只读 `list<string>` 用 `list<string>::const_iterator`；需要经迭代器修改元素时使用 `list<string>::iterator`。

## 9.9–9.10 begin 与 cbegin

非 `const` 容器的 `begin()` 返回可写迭代器，常量容器的 `begin()` 返回常量迭代器；`cbegin()` 总返回常量迭代器。因此题中 `it1` 是 `vector<int>::iterator`，`it2`、`it3`、`it4` 都是 `vector<int>::const_iterator`。

## 9.11 六种 vector 初始化

```cpp
std::vector<int> empty;             // 空
std::vector<int> copy(original);    // 与 original 相同
std::vector<int> copy2 = original; // 与 original 相同
std::vector<int> range(first, last); // 复制 [first, last)
std::vector<int> values{1, 2, 3};  // 1、2、3
std::vector<int> zeros(3);         // 三个 0
std::vector<int> sevens(3, 7);     // 三个 7
```

这里分别展示默认、复制、范围、列表、指定数量和数量加初值六类方式；复制初始化还展示了另一种写法。花括号优先匹配列表初始化：`{3, 7}` 是两个元素，不是三个 7。

## 9.12 容器拷贝与迭代器范围构造

直接拷贝要求容器类型和元素类型相同；迭代器范围构造可来自不同容器，只要范围有效且元素可转换为目标元素类型。范围构造也可只复制一段。

## 9.13 int 容器构造 vector<double>

[ex9_13.cpp](ex9_13.cpp) 对 `list<int>` 和 `vector<int>` 都使用迭代器范围构造 `vector<double>`；每个 `int` 可转换为 `double`。不能直接以不同元素类型的整个容器调用同类型拷贝构造。

## 后续

9.14 起、赋值、插入删除、失效规则、`string` 与容器适配器习题待整理。
