# 第 10 章：泛型算法

已核对并整理 10.1–10.42（书页 336–388 / PDF 页 362–414）。知识复习见 [复习提纲](REVIEW.md)。

## 10.1–10.2 用 count 统计

[ex10_01_02.cpp](ex10_01_02.cpp) 对 `vector<int>` 与 `list<string>` 分别调用 `std::count`。示例容器是 `1 2 3 4 2 2` 与 `the quick the turtle`，输入 `2 the` 时输出两个序列中值 2 出现 3 次、单词 `the` 出现 2 次。`count` 要求元素类型与给定值之间可用 `==` 比较，函数本身返回计数值而不是迭代器。

## 10.3–10.4 用 accumulate 求和

[ex10_03_04.cpp](ex10_03_04.cpp) 先把读入的整数求和，再对 `vector<double>{0.5, 1.5, 2.5}` 演示 10.4 的陷阱：`accumulate(vec.cbegin(), vec.cend(), 0)` 的和的类型由第三个实参决定，是 `int`。每一步 `acc + *iter` 的结果写回 `int` 时都被截断，逐步得到 0、1、3，最终输出 3 而不是 4.5；初值改成 `0.0` 后得到正确的 4.5。编译该行时 `/W4` 会给出 C4244 转换警告，恰好印证了题目指出的类型问题。

## 10.5 equal 与 C 风格字符串

`equal` 用 `==` 比较两个范围中的元素。对 `list<const char*>`，`==` 比较的是指针地址，不是字符串内容。只有当两个序列保存同一批指针（例如都指向同一处字面量）时结果才有意义；各自独立存储的相同内容会被判为不相等，内容不同但地址巧合相同的可能性虽然极小，语义上也无法依赖。要按内容比较，应先把元素换成 `string`，或改用逐字符比较。

## 10.6–10.7 fill_n 与目的容器

[ex10_06_07.cpp](ex10_06_07.cpp) 演示三件事：对已有 5 个元素的序列调用 `fill_n(v.begin(), v.size(), 0)` 清零；10.7(a) 先 `resize` 再 `copy`，因为 `copy` 不会为目标创建元素；10.7(b) `reserve(10)` 只改变容量，`vec.begin()` 后面仍没有可写的元素，改用 `std::back_inserter(filled)` 让 `fill_n` 通过 `push_back` 写入 10 个 0。

## 10.8 back_inserter 与容器大小

`back_inserter` 是 `<iterator>` 中定义的迭代器适配器。解引用它时会调用容器的 `push_back` 创建新元素，因此"向不存在的元素写入"被转换为"插入新元素"。改变容器大小的责任落在迭代器适配器与容器成员上，算法本身不承担这一职责。

## 10.9 消除重复单词

[ex10_09.cpp](ex10_09.cpp) 读入单词后先 `sort`，使重复元素相邻，再对 `unique` 的返回值调用 `erase` 收缩容器。输入书上的句子得到 `fox jumps over quick red slow the turtle`。`unique` 只把不重复的值搬到前部并返回新的逻辑结尾，容器大小并不改变，多余的元素仍占着内存。

## 10.10 算法从不改变容器大小

算法通过迭代器读写元素，没有任何一个标准库泛型算法直接添加或删除元素；`unique`、`remove` 等只是重排或覆盖元素并返回新范围。增删元素始终由容器成员或插入迭代器完成，这一设计让算法不必了解具体容器的接口。

## 10.11 按长度稳定排序

[ex10_11.cpp](ex10_11.cpp) 在 `elim_dups` 之后调用 `std::stable_sort(words.begin(), words.end(), is_shorter)`。稳定排序保证长度相同的单词维持字典序。示例输出 `fox red the over slow jumps quick turtle`。

## 10.12 按 ISBN 排序 Sales_data

[ex10_12_13.cpp](ex10_12_13.cpp) 定义 `compare_isbn(lhs, rhs)` 比较 `isbn()`，作为 `sort` 的第三个实参。`Sales_data` 复用 [第 7 章](../ch07/Sales_data.h) 的头文件；示例中 `0-201-70353-X` 的两条记录被排在一起。

## 10.13 partition 分割单词

同一源码用 `std::partition(words.begin(), words.end(), at_least_five)` 把长度不小于 5 的单词移到前部，返回值是第一个不满足谓词的元素。示例中前半段是 `jumps turtle quick`，后半段是 `fox red slow`；`partition` 不保证两段内部的相对顺序。

## 10.14–10.15 两个入门 lambda

[ex10_14_15.cpp](ex10_14_15.cpp) 给出接受两个 `int` 返回之和的 lambda，以及捕获局部变量 `base`、接受一个 `int` 参数的 lambda。没有捕获的 lambda 可以转换为函数指针；带捕获的则不能。

## 10.16/10.18/10.19 biggies 的三个版本

[ex10_16_18_19.cpp](ex10_16_18_19.cpp) 实现书中的 `biggies`：先 `elim_dups`，再按长度稳定排序，然后分别用三种方式定位长单词。

- 10.16 用捕获 `sz` 的 lambda 作为 `find_if` 的谓词，输出从第一个长单词到结尾的范围。
- 10.18 改用 `partition`。注意方向与 `find_if` 相反：满足谓词的元素被移到序列前部，长单词在 `[begin, 返回值)` 中。
- 10.19 改用 `stable_partition`，长单词保持排序后的顺序，短单词也维持原有相对顺序。

输入长度 5 时三个版本都报告 3 个长单词 `jumps quick turtle`；`partition` 版本内部顺序为 `turtle quick jumps`，是不确定的。

## 10.17 用 lambda 重写排序与分割

[ex10_17.cpp](ex10_17.cpp) 把 10.12 和 10.13 的函数替换为就地定义的 lambda：排序比较器捕获空列表，分割谓词同样不需要捕获。输出与函数版本一致。

## 10.20 count_if 统计长单词

[ex10_20.cpp](ex10_20.cpp) 用捕获 `sz` 的 lambda 调用 `count_if`，统计长度大于 6 的单词。示例词表中这样的单词有 4 个。

## 10.21 递减到零的 lambda

[ex10_21.cpp](ex10_21.cpp) 的 lambda 按值捕获 `countdown` 并标记 `mutable`，每调用一次递减一次，返回捕获副本是否已经为 0。副本变为 0 后再调用只返回 `true`，不再递减；原始变量保持为 3，这也演示了按值捕获与原变量的隔离。

## 10.22–10.24 bind 与占位符

[ex10_22_24.cpp](ex10_22_24.cpp) 用 `std::bind(check_size, _1, 6)` 生成 `count_if` 的谓词，重做 10.20 的统计（此处谓词条件是"不短于 6"，示例词表中没有恰好 6 个字母的单词，两种条件结果相同）。10.24 要在 `int` 向量中找第一个大于给定字符串长度的值，占位符传递的是 `int`，因此辅助函数 `value_exceeds` 把 `string::size_type` 形参放在第一位；若沿用 `check_size` 的形参顺序，占位符就得把 `int` 转换成 `string`，无法编译。

10.23：`bind` 接受一个可调用对象，再加上与该对象形参个数相同的实参；其中若干实参可以是占位符，其余是绑定值。调用生成对象时，占位符对应位置由调用方补足，绑定值固定不变。占位符定义在 `std::placeholders` 中。

## 10.25 biggies 的 bind 版本

[ex10_25.cpp](ex10_25.cpp) 用 `std::bind(check_size, _1, sz)` 替代捕获 `sz` 的 lambda，其余流程与 10.16 相同，仍用 `find_if` 定位第一个长单词并输出。

## 10.26 copy 为什么需要插入迭代器

`copy(vec.cbegin(), vec.cend(), dest.begin())` 假设 `dest.begin()` 之后已有足够的元素可写。目的容器为空时，这个范围无效，向其中写入是未定义行为。`back_inserter(dest)` 通过 `push_back` 逐个创建元素，`inserter` 与 `front_inserter` 则分别使用 `insert` 和 `push_front`。

## 10.27–10.28 unique_copy 与三种插入迭代器

[ex10_27_28.cpp](ex10_27_28.cpp) 先对源向量排序，再用 `unique_copy` 和 `back_inserter` 把不重复的值收集进 `list`。随后把同一个五元素向量分别复制到三个 `list`：`inserter(l, l.end())` 与 `back_inserter` 得到 `1 2 3 4 5`，`front_inserter` 每次都把新值放到最前，得到 `5 4 3 2 1`。

## 10.29–10.31 流迭代器

[ex10_29_31.cpp](ex10_29_31.cpp) 以文件名作为命令行参数，用 `istream_iterator<string>` 把整个文件读进 `vector<string>`；再从标准输入读取整数，排序后分别用 `copy` 和 `unique_copy` 写入 `ostream_iterator<int>`（分隔符为一个空格）。流迭代器用构造时绑定的流读取，`operator++` 前进并在流失效时到达尾后迭代器。

## 10.32 书店程序的算法版

[ex10_32.cpp](ex10_32.cpp) 复用 [第 1 章](../ch01/Sales_item.h) 的 `Sales_item`，把事务读入 `vector` 后按 ISBN 排序，用 `equal_range` 定位同一 ISBN 的范围，`accumulate` 从 `Sales_item(isbn)` 起累加并输出每组汇总。对 `../ch01/data/grouped_sales.txt` 的输出是 `0-201-70353-X 5 120 24`、`0-201-78345-X 5 110 22`、`0-201-82470-1 1 30 30`，即 ISBN、册数、总额与均价。

## 10.33 按奇偶拆分文件

[ex10_33.cpp](ex10_33.cpp) 接受输入文件和两个输出文件名，`istream_iterator<int>` 逐个读取，余数为 0 写入偶数文件，否则写入奇数文件；`ostream_iterator` 以空格分隔。对 `data/integers.txt` 的结果是偶数 `2 4 6 8 10`、奇数 `1 3 5 7 9`。负奇数的 `% 2` 是 -1 而不是 1，因此判断条件应写成 `== 0`。

## 10.34–10.35 逆序打印

[ex10_34_37.cpp](ex10_34_37.cpp) 用 `copy(values.crbegin(), values.crend(), out)` 通过反向迭代器逆序打印，再用普通迭代器从 `cend()` 开始逐步 `--it` 打印。两种写法输出相同；反向迭代器版本依赖 `rbegin/rend` 的适配，普通迭代器版本需要小心不要在解引用 `cend()` 之后才递减。

## 10.36 找 list 中最后一个 0

对反向迭代器调用 `find(list.rbegin(), list.rend(), 0)`，找到的是逆序中的第一个 0，即正序中的最后一个。示例列表 `0 1 2 3 4 0 6 7 0 9` 中它的下标是 8。反向迭代器通过 `base()` 回到普通迭代器时指向原元素的下一个位置，需要先递减再计算距离。

## 10.37 反向复制一段元素

同一个源码把列表下标 3 到 7 的元素按逆序复制到向量。反向迭代器 `rbegin() + k` 对应正序下标 `size() - 1 - k`，因此复制范围取 `[rbegin()+2, rbegin()+7)`。对示例列表输出 `7 6 0 4 3`（下标 5 的元素本来就是 0）。

## 10.38 迭代器类别

| 类别 | 能力 | 支持的操作 |
| --- | --- | --- |
| 输入迭代器 | 只读、单遍 | `==`、`!=`、`++`、`*`、`->`，如 `istream_iterator`、`find` |
| 输出迭代器 | 只写、单遍 | `++`、`*`，如 `ostream_iterator`、`back_inserter` |
| 前向迭代器 | 读写、多遍 | 输入迭代器的能力加多遍扫描，如 `forward_list`、`replace` |
| 双向迭代器 | 前向能力加倒退 | `--`，如 `list`、`reverse` |
| 随机访问迭代器 | 双向能力加快速跳转 | `<`、`<=`、`+`、`-`、`it[n]`、`+=`，如 `vector`、`sort` |

## 10.39 list 与 vector 的迭代器类别

`list` 迭代器是双向迭代器；`vector` 迭代器是随机访问迭代器。

## 10.40 算法要求的最低迭代器类别

`copy` 至少需要输入迭代器读源、输出迭代器写目标；`reverse` 需要双向迭代器；`unique` 需要前向迭代器。要求更高的算法不能用于只提供较弱迭代器的容器，例如不能对 `list` 直接调用 `sort`。

## 10.41 replace 算法族

| 算法 | 行为 |
| --- | --- |
| `replace(beg, end, old_val, new_val)` | 就地把每个等于 `old_val` 的元素替换为 `new_val` |
| `replace_copy(beg, end, dest, old_val, new_val)` | 不修改原范围，把替换后的序列写入 `dest` |
| `replace_if(beg, end, pred, new_val)` | 就地替换满足 `pred` 的元素 |
| `replace_copy_if(beg, end, dest, pred, new_val)` | 满足 `pred` 的元素在写入 `dest` 的副本中被替换 |

## 10.42 list 上的消重

[ex10_42.cpp](ex10_42.cpp) 读入单词后调用 `list` 的成员 `sort` 与 `unique`。成员 `unique` 直接删除相邻重复元素，不需要再调用 `erase`；这也是 `list` 提供成员版本的原因——成员函数以链接指针的方式重排和删除节点，不必满足算法对迭代器的要求。

## 验证记录

本轮 19 个程序使用 MSVC 19.29（VS2019 BuildTools，14.29.30133）、`/std:c++17`、`/EHsc`、`/W4` 编译，源码按书中 C++11 风格编写。统计、排序、分割、lambda 与 bind、插入迭代器、流迭代器、反向迭代器和书店汇总均用上述样例实际运行核对；`ex10_33` 生成的两个输出文件内容已检查。唯一的编译警告来自 `ex10_03_04` 第 21 行的 C4244，它正是 10.4 要求分析的双转 int 转换，属预期现象。个人复习完成后再勾选 [复习提纲](REVIEW.md) 中的检查项。
