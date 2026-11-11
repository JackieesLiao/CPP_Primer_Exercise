# 第 14 章：重载运算与类型转换

已核对并整理 14.1–14.54（书页 500–565 / PDF 页 526–591）。知识复习见 [复习提纲](REVIEW.md)。本章部分运算符按题意直接扩展到了 ch12/ch13 的类上：[StrBlob.h](../ch12/StrBlob.h) 增加了相等与关系运算、StrBlobPtr 的自增自减与算术、ConstStrBlobPtr 的 `*` 与 `->`；[StrVec.h](../ch13/StrVec.h) 增加下标与列表赋值；[String.h](../ch13/String.h) 增加只读下标。原有程序的行为不变。

## 14.1–14.5 运算符的基础

重载运算符与内置运算符的差别：优先级、结合性和操作数求值顺序固定（`&&`、`||` 不再有短路保证）；本意相同、行为一致最重要。14.3 中 `"str" < "ptr"` 与指针比较是内置的，两个 `string`、两个 `vector<int>` 用的是重载版本。14.4 中 `s1 == s2` 等也可以是成员或非成员，但 `s1 + s2` 类的对称运算符通常非成员，`+=`、下标、自增、箭头和解引用是成员。14.5 的例子：两个 `Money` 相加、`Date` 加天数。

## 14.2–14.15 Sales_data 的运算符

[Sales_data.h](Sales_data.h) 给出完整实现；[ex14_02_09.cpp](ex14_02_09.cpp) 读入一条记录（`0-201-70353-X 4 24.99`），输出格式化结果（14.6/14.9）、ISBN 相同的 `+` 汇总（14.2）、`==`/`<`（14.2），以及 ISBN 不同时 `operator+` 抛出的 `runtime_error`。14.10 的读入中多余字段留在流里，格式错误使流失效；14.11 的错误版本不检查流状态，读取失败仍会使用未定义的数据；14.12 的检查就是 `if (input)`。14.13 的 `+=` 有成员与非成员两种等价形式；14.14 中复合赋值返回引用（避免多余拷贝且符合内置语义）；14.15 的 `Employee` 不该有 `operator+`——加两个员工没有领域意义。

## 14.16–14.21 相等与关系运算

[ex14_16_18.cpp](ex14_16_18.cpp) 演示 StrBlob/StrBlobPtr/StrVec 的 `==`、`!=`、`<`：StrBlob 比较底层 vector；StrBlobPtr 先比内容再比位置。14.17 的 Book/Sales_data 按 ISBN 比较；14.19 的 Book `<` 同理。14.20 的 `+=` 返回 `Sales_data&`，`+` 返回值；14.21 把 `+` 实现为"拷贝后 += 的返回"，书中的另一版直接用 `+=` 的结果按值返回，行为相同但本仓库的实现先检查 ISBN。

## 14.22–14.26 特殊赋值与下标

[ex14_22_45.cpp](ex14_22_45.cpp) 演示 `operator=(const std::string&)` 把 ISBN 直接赋给对象。[ex14_23_28.cpp](ex14_23_28.cpp) 演示 StrVec 的初始化列表赋值（14.23）与 `operator[]` 读写（14.26）。14.24 需要混合类型赋值的类：`Date = string`、`Money = double` 一类。14.25 的下标必须检查范围并抛出 `out_of_range` 或返回默认值，本仓库的实现依赖调用者保证，容器类内部已检查。

## 14.27–14.32 迭代器式运算符

[ex14_16_18.cpp](ex14_16_18.cpp) 与 [ex14_30_32.cpp](ex14_30_32.cpp) 演示 StrBlobPtr 的 `++`/`--`（前缀返回引用，后缀返回旧值副本）、`+`/`-` 与下标，以及 ConstStrBlobPtr 的 `*` 和 `->`（`it->size()` 等价于 `(*it).size()`）。14.31：StrBlobPtr 的箭头并非必需，但保留它使两个迭代器接口对称。14.32 的 `StrBlobPtrProxy` 用 `operator->` 把调用转发给持有的迭代器。

## 14.34–14.41 函数对象

[ex14_34_36.cpp](ex14_34_36.cpp) 实现条件运算符风格的 `IfThenElse` 和可作循环条件的 `ReadString`（14.35/14.36 读两行输入）。[ex14_37_38.cpp](ex14_37_38.cpp) 的 SwapCheck 检查交换是否真的改变了值，SizeCheck 匹配指定长度。14.39 的两个计数器见 [ex14_39.cpp](ex14_39.cpp)（长于 5 与恰为 1 的单词数）。14.40/14.41：用函数对象替换 elimDups 里的 lambda 完全可行；lambda 简短直观，需要复用、带状态或按模板适配多种类型时，函数对象更好。

## 14.42–14.44 标准库函数对象与 function

[ex14_42.cpp](ex14_42.cpp) 用 `bind` 组合 `greater`、`not_equal_to`、`multiplies` 完成 (a)(b)(c) 三问。[ex14_44.cpp](ex14_44.cpp) 的计算器用 `map<string, function<int(int,int)>>` 分发运算。遇到未知运算符、除零或结果超出 `int` 范围时，程序报告错误并继续读取下一条表达式。

## 14.45–14.54 类型转换运算符

14.45 的 `operator std::string` 与 `operator double` 在 [Sales_data.h](Sales_data.h)。14.46 认为二者应标 `explicit`，否则 `"0-201" == item` 之类表达式会产生意外转换；演示中用 `static_cast` 保持意图。14.47 中 `operator int` 与 `operator bool` 的差别：int 参与算术，bool 只用于条件。14.48/14.49 的 Date 类 [ex14_48_49.cpp](ex14_48_49.cpp) 用 `operator bool` 判断日期合法性，可直接出现在 if 中。14.50 的两个赋值在转换链上产生二义或截断；14.51 中 `double + SmallInt` 命中 `operator+(int, int)` 的提升路径，而重载 `operator+(double, SmallInt)` 时则是精确匹配，优先级高于内置版本。

## 验证记录

本轮 12 个程序使用 CMake（NMake + MSVC 19.29、`cxx_std_11`、`/W4 /utf-8`）构建并全部运行：Sales_data 的运算与异常、迭代器运算符、函数对象计数、bind 组合、function 计算器与 Date 的 bool 转换均与题解一致。个人复习完成后再勾选 [复习提纲](REVIEW.md) 中的检查项。
