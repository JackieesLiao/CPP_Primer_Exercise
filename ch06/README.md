# 第 6 章：函数

已核对并整理 6.1–6.56（书页 184–246 / PDF 页 210–272）。知识复习见 [复习提纲](REVIEW.md)。

## 6.1–6.2 形参与实参

形参是函数声明的变量，实参是调用时提供的初值；无参函数的形参列表写 `void` 或留空。6.2 的四处错误分别是：参数类型放错（`int v1` 应为 `double`）、返回值类型不符、漏写返回值、形参名重复。

## 6.3–6.4 阶乘

[ex6_03_04.cpp](ex6_03_04.cpp) 用 `long long` 实现阶乘。每次乘法前都检查结果是否可表示。以 64 位 `long long` 为例，20! 得到 2432902008176640000，21! 会报告结果超出范围。负数输入会收到单独的错误提示。

## 6.5–6.7 局部静态与绝对值

[ex6_05.cpp](ex6_05.cpp) 返回 `int` 的绝对值。[ex6_07.cpp](ex6_07.cpp) 的 `call_count` 用局部 `static unsigned calls` 记录调用次数，输出 `call 1 2 3`。局部静态对象在首次执行到定义时初始化，函数结束后仍然存活。

## 6.8–6.9 头文件与分离编译

`Fact.h` 放声明，`Fact.cc` 放定义并包含自己的头文件；两个头文件加包含保护。`#ifndef/#define/#endif` 防止同一头文件被重复展开，否则会重复定义。

## 6.10–6.12 指针与引用传参

[ex6_10_12.cpp](ex6_10_12.cpp) 分别用指针和引用交换两个 `int`。引用版本在调用点看不出是交换，容易误读，但书写最简洁；指针版本显式传递地址。复制实参的写法无法影响调用方的对象。

## 6.13–6.16 形参选择的依据

只读大对象用 `const` 引用，避免拷贝；需要修改就用普通引用；小对象直接传值。`void print(std::ostream &os, const std::string &s)` 之类声明注明了读与写的边界。6.15 中试图用 `const char` 形参返回两个 `char` 之一的写法不行——`char` 太小且按值传递，两个都返回不了。

## 6.17 大小写处理

[ex6_17.cpp](ex6_17.cpp) 的 `contains_uppercase` 只读字符串，参数是 `const std::string&`；`to_lowercase` 要修改，参数是普通引用。能否修改决定了形参的选择，这也是 `const` 表达接口意图的方式。

## 6.18–6.20 函数声明与返回引用

6.18 的两个声明：`bool compare(const matrix &, const matrix &);`（`matrix` 需先 `typedef`）与 `vector<int>::iterator change_val(int, vector<int>::iterator);`。6.19 的调用逐一检查实参个数与类型是否匹配，(b) 缺实参、(c) 多余实参、(d) 类型不符。6.20：引用形参能避免拷贝并支持写入，但使调用点含义不直观，需要修改时才用。

## 6.21–6.24 数组形参

[ex6_21_24.cpp](ex6_21_24.cpp) 实现 `bigger`、交换指针所指值，以及带 `begin/end` 的 `print_array`。6.23 的要点是形参必须携带长度：用首尾指针或引用到数组的引用。6.24 的 `print(const int ia[10])` 里 10 只是注释，实参传 `10` 会把指针当作长度使用——数组形参永远是指针。

## 6.25–6.27 main 的参数与 initializer_list

[ex6_25_27.cpp](ex6_25_27.cpp) 把 `argv[1]` 起的参数连接成串（`alpha beta` 得到 `alphabeta`）、逐行打印参数、用 `initializer_list<int>` 求和。`argv[0]` 是程序名，`argv[argc]` 是空指针。

## 6.28–6.32 返回类型细节

`initializer_list` 的元素是 `const`。`int &get(int *array, int index) { return array[index]; }` 返回引用可作左值使用（6.32）；返回局部变量的引用或指针会悬垂，函数结束时所指对象已经销毁（6.31）。

## 6.33 递归打印

[ex6_33.cpp](ex6_33.cpp) 以"打印当前下标再处理下一个"的方式递归输出 `vector<int>`，到达 `size()` 时结束。列表实现也可以，递归深度受栈限制。

## 6.34–6.35 递归的边界

阶乘递归的基准情形是 `val <= 1`；改成 `val != 0` 时负数会一直递减永不停止，栈被耗尽后程序崩溃——递归必须保证向基准情形推进。

## 6.36–6.38 返回数组指针

[ex6_38.cpp](ex6_38.cpp) 用尾置返回类型 `auto arr10() -> int (*)[10]` 返回指向 10 个 `int` 的数组的指针，`static` 数组保证返回后仍然有效；`typedef int ArrayOfTen[10];` 与 `decltype` 两种写法在注释中给出。输出 0–9。

## 6.39–6.40 重载与默认实参

仅返回类型不同的两个函数不是重载，重声明出错；`f(int, int)` 与 `f(double, double)` 同时存在时传 `int` 与 `double` 混合的调用产生二义性。默认实参只能加一次，声明和定义分属两处时会造成重复默认值。

## 6.41–6.42 默认实参的匹配

`char screen(int height = 3, char background = ' ')`：`screen(24, 'A')` 都显式给出；`screen()` 都用默认；`screen('A')` 会把字符转成 int 传给 `height`，这正是默认实参按位置匹配的陷阱。

## 6.43–6.47 内联、constexpr 与调试

[ex6_44.cpp](ex6_44.cpp) 把 `is_shorter` 标记为 `inline`，短函数内联避免调用开销。6.45 的 `isShorter` 不适合 `constexpr`——它调用 `string::size()` 且依赖运行期对象。6.46 的判断同理。6.47 的 NDEBUG 条件块：

```cpp
if (verbose)
{
#ifndef NDEBUG
    std::cerr << "starting word transform\n";
#endif
}
```

## 6.48–6.52 重载解析

`cin >> word` 与 `word == "done"` 的组合等价于 `while (std::cin >> word && word != "done")`，两者都是 bool。6.51 的三个版本（[ex6_51.cpp](ex6_51.cpp)）输出 `f()`、`f(int 42)`、`f(int 42, int 0)`、`f(double 2.56, double 3.14)`；`f(2.56, 42)` 一行被注释掉，因为 `double/int` 对两个版本都是不精确匹配，调用二义。

## 6.53–6.56 函数指针

6.53 的两组声明等价：引用与指针形参的写法不改变匹配。6.54 的形参类型是 `int (*)(int, int)`，指向函数的指针类型由返回类型与形参列表决定；函数名会自动转换为指针。[ex6_54_56.cpp](ex6_54_56.cpp) 把加减乘除四个函数放进 `vector<Operation>`（`Operation` 是函数指针别名），循环调用得 `16 8 48 3`，函数指针的解引用可以省略。

## 验证记录

本轮 12 个程序使用 MSVC 19.29（VS2019 BuildTools，14.29.30133）、`/std:c++17`、`/W4` 编译，按上述样例运行核对：阶乘边界、静态计数、两种交换、重载选择与函数指针调用均与答案一致。个人复习完成后再勾选 [复习提纲](REVIEW.md) 中的检查项。
