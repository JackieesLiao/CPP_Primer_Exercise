# 第 12 章：动态内存

已核对并整理 12.1–12.32（书页 400–463 / PDF 页 426–489）。知识复习见 [复习提纲](REVIEW.md)。

## 12.1 StrBlob 的共享语义

`b2 = {{"a", "an", "the"}}` 让 `b2.data` 与新临时对象共享；`b1.push_back("about")` 只影响 `b1` 的元素。当 `b1` 与 `b2` 都由花括号列表构造时二者不共享数据；若 `b2` 是 `b1` 的拷贝，push_back 后两个都能看到新元素。

## 12.2–12.5 StrBlob 类

[StrBlob.h](StrBlob.h) 给出完整实现：`check` 抛出 `out_of_range`，`front`/`back` 提供 const 重载（[ex12_02.cpp](ex12_02.cpp) 演示空容器时捕获 `front on empty StrBlob`）。12.3：const 版本的 `push_back`/`pop_back` 没有意义——修改容器的函数不应是 const 成员。12.4：`check` 里 `i >= data->size()` 中 `i` 是 `size_type`（无符号），永远不会小于 0，因此不需要检查负值。12.5：接受 `initializer_list` 的构造函数未标 `explicit`，允许 `StrBlob s = {"a", "b"};` 的拷贝初始化——方便但会掩盖一次构造；标了 `explicit` 只能直接初始化，接口意图更明确。

## 12.6–12.7 new/delete 与 shared_ptr

[ex12_06_07.cpp](ex12_06_07.cpp) 按题目要求把"分配—打印—释放"分别写成裸指针版（`new`/`delete`）与 `make_shared` 版。裸版本必须记得 `delete`，shared_ptr 版本在最后一个使用者离开时自动释放。

## 12.8–12.13 泄漏与所有权的错误

- 12.8 中 `p = new int; p = 0;` 让唯一的地址被 0 覆盖，该 int 永远无法释放，是泄漏。
- 12.9 的两段代码里 `q` 先后指向动态对象与局部对象地址，同样丢失了释放途径；`r = q` 后 `r` 的原对象泄漏。
- 12.10 中 `process(shared_ptr<int>(p2))` 正确：临时 shared_ptr 与 `p2` 共享计数，调用结束减一，不会误删。
- 12.11 的 `process(shared_ptr<int>(p.get()))` 错误：临时智能指针以裸指针接管所有权，结束时把 `p` 的对象删掉，此后 `p` 悬垂。
- 12.12 的四个语句中只有 `sp(new int('a'))`、`p2(new int(*p))`、`p.reset(new int(42))` 一类"以裸指针构造智能指针、把裸指针交给 reset"的形式合法；把智能指针的 `get()` 结果再交给另一个智能指针会双重释放。
- 12.13 中 `sp.reset()` 释放所指对象后 `sp` 为空，可以继续使用；`wp2.reset()` 只断开 weak_ptr，不影响对象生存期。

## 12.14–12.15 连接的清理

[ex12_14_15.cpp](ex12_14_15.cpp) 用 `shared_ptr<Connection>` 管理连接：12.14 传入命名函数 `end_connection`，12.15 改传 lambda。两个版本输出一致——`opening` 后打印 `working with`，离开作用域时自动 `closing`，即使中途抛出异常也会清理。

## 12.16–12.18 unique_ptr 的约束

`unique_ptr` 的拷贝构造与拷贝赋值被删除，因此 12.16 的两个语句都无法编译；所有权只能用 `release` 或 `reset` 转移。12.17 中 (a)(c) 悬垂风险（`p` 来自局部对象）、(e) 用 `get()` 构造两个所有者、(f) 把 `p2` 交给 `unique_ptr` 会导致重复释放；(b)(d) 合法。12.18：`shared_ptr` 允许多个所有者，不存在"交出所有权"的概念，因此没有 `release`。

## 12.19–12.22 StrBlobPtr 与 ConstStrBlobPtr

[StrBlob.h](StrBlob.h) 定义了 `StrBlobPtr`（12.19）：用 `weak_ptr` 指向元素的 vector，`deref` 先 `lock` 并检查下标，`increment` 推进并检查越界。12.21 的两种 `deref` 写法中，书中的合并写法紧凑但把检查、取值揉在一起，显式版本更易调试——本仓库采用显式版本。12.22 的 `ConstStrBlobPtr` 接受 `const StrBlob&`，内部持有 `weak_ptr<const vector<string>>`，`deref` 返回 `const string&`。[ex12_19_20_22.cpp](ex12_19_20_22.cpp) 逐行读入文件后分别用两种迭代器遍历，输出相同。

## 12.23–12.26 动态数组

[ex12_23.cpp](ex12_23.cpp) 用 `new char[]` 拼接两个字符数组（长度 = 两串之和 + 1），再用 `string` 重做同样的事（MSVC 对 `strcpy/strcat` 给出 C4996 弃用警告，本题即为练习它们）。[ex12_24.cpp](ex12_24.cpp) 读入未知数量的字符：数组满时倍增容量、拷贝、`delete[]` 旧块。[ex12_26.cpp](ex12_26.cpp) 演示三种管理方式：`new int[10]()` 值初始化、`unique_ptr<int[]>`（C++11 起支持下标）、`shared_ptr<int>` 加 `default_delete<int[]>` 删除器——`shared_ptr<T[]>` 与其下标运算符是 C++17 的特性，此处按 C++11 基线用 `get()[i]` 访问。12.25：`delete pa;` 应为 `delete[] pa;`，否则行为未定义。

## 12.27–12.31 文本查询程序

[TextQuery.h](TextQuery.h) 实现书中设计：`TextQuery` 持有 `shared_ptr<vector<string>>` 的行文本和 `map<string, shared_ptr<set<LineNo>>>`；`query` 返回共享这些数据的 `QueryResult`，`print` 输出出现次数与各行原文。[ex12_27.cpp](ex12_27.cpp) 对 [data/story.txt](data/story.txt) 的查询输出如 `CMake occurs 4 time(s)`（第 1、2、5、7 行）与 `missing occurs 0 time(s)`。

- 12.28：不用库容器时需要自己实现词汇表、行号表与文本行管理，对应第 7 章之前的裸 new 方案，容易泄漏。
- 12.29：`while` 与 `do while` 都能实现查询循环；`do while` 至少执行一次的特性更适合"先提示再读取"，但 while 使循环条件一目了然。
- 12.30：类定义即 [TextQuery.h](TextQuery.h)。
- 12.31：`QueryResult` 用 `set` 保存行号——行号天然唯一且需要升序；`vector` 会为同一单词的多次出现保存重复行号，还得手动排序去重。

## 12.32 StrBlob 版文本查询

[StrBlobTextQuery.h](StrBlobTextQuery.h) 把行文本换成 `StrBlob`，结果类提供返回 `ConstStrBlobPtr` 的 `begin`/`end`，不再暴露 vector 本身。[ex12_32.cpp](ex12_32.cpp) 与 12.27 版本对同一文件、同一批查询的输出完全一致。

## 验证记录

本轮 9 个程序使用 CMake（NMake + MSVC 19.29、`cxx_std_11`、`/W4 /utf-8`）构建，全部按上述样例运行核对；StrBlob 的越界异常、连接的自动清理、动态数组扩容与两套文本查询程序的实际输出均与题解一致。个人复习完成后再勾选 [复习提纲](REVIEW.md) 中的检查项。
