# 第 19 章：特殊工具与技术

已核对并整理 19.1–19.28（书页 845–910 / PDF 页 871–936）。知识复习见 [复习提纲](REVIEW.md)。

## 19.1–19.2 定制内存分配

`allocator<T>` 把分配与构造分离：`allocate(n)` 拿原始内存，`construct` 在其上构造，`destroy` 后 `deallocate` 归还。19.1 分析 vector 扩容中的分配行为，19.2 用 allocator 重写 StrVec 的管理逻辑——与 ch13 的 [StrVec.h](../ch13/StrVec.h) 一致。

## 19.3–19.10 运行期类型识别

`dynamic_cast<Derived*>(base_pointer)` 失败返回空指针（19.6），引用版本失败抛 `bad_cast`（19.7），`typeid` 比较不需要转换（19.8），三者见 [ex19_06_08.cpp](ex19_06_08.cpp)（复用 ch15 的 Quote 层级，三种写法都报告 Bulk_quote 并算出对应折扣价）。19.9 的类型名打印见 [ex19_09_10.cpp](ex19_09_10.cpp)：MSVC 输出装饰名，如 `class std::vector<int,class std::allocator<int> >`。19.10 的静态类型判断依据与 ch15 相同。

## 19.11–19.19 成员指针

成员指针存储"相对类"的偏移，必须绑定对象后使用：`screen.*title_member` 与 `pointer->*menu.at("forward")()`（19.12–19.17）。[ex19_14_18.cpp](ex19_14_18.cpp) 的菜单表把字符串映射到 `Screen &(Screen::*)()`；19.18 用 `std::bind` 组合 `&std::string::size` 作 count_if 谓词，长于 6 的单词有 2 个。[ex19_19.cpp](ex19_19.cpp) 用同样的手法在 `vector<Sales_data>` 中按 `isbn()` 查找第一条匹配。

## 19.20–19.25 嵌套类与 union

19.20 的 TextQuery::QueryResult 即嵌套类答案（ch12/ch15 已采用）。[ex19_21_25.cpp](ex19_21_25.cpp) 实现带拷贝控制的 `Token`：匿名 union 存 `char/int/double/string`，判别式记录活跃成员；string 成员用 placement new 构造、显式析构销毁，赋值运算符按当前类型分支处理。运行输出展示 char/int/double/string 四态切换与拷贝。

## 19.26–19.28 链接指示

`extern "C"` 声明使 C++ 函数按 C 约定命名以便互相调用（19.26）；类成员不能标 `extern "C"`（19.27）；`extern "C"` 的函数仍可带 C++ 类型形参，只是按 C 的函数名导出（19.28）。这些属于声明层面，本仓库的 CMake 构建未引入 C 源文件，讨论见本节。

## 验证记录

本轮 5 个程序使用 CMake（NMake + MSVC 19.29、`cxx_std_11`、`/W4 /utf-8`）构建并全部运行：RTTI 三式、成员指针菜单、mem_fn 查找与 Token 的 union 拷贝控制均与题解一致。个人复习完成后再勾选 [复习提纲](REVIEW.md) 中的检查项。
