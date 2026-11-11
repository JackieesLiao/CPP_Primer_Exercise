# 第 15 章：面向对象程序设计

已核对并整理 15.1–15.43（书页 560–622 / PDF 页 586–648）。知识复习见 [复习提纲](REVIEW.md)。

## 15.1–15.3 Quote 与虚函数

虚成员是"可以在派生类中覆盖、通过引用或指针调用时按动态类型绑定"的成员。`private` 只有类自身可见，`protected` 还允许派生类访问。[Quote.h](Quote.h) 的 `Quote::net_price` 是虚函数，`print_total` 通过 `Quote&` 调用；[ex15_03_05_11.cpp](ex15_03_05_11.cpp) 对三类书分别输出 `200`、`160`（满 5 件 8 折）与 `182`（前 3 件 7 折）。

## 15.4–15.7 派生类

15.4 的声明中把派生类自身当基类不合法，类名的先行声明不含派生列表。[ex15_03_05_11.cpp](ex15_03_05_11.cpp) 里的 `Bulk_quote`（15.5/15.6）；[Quote.h](Quote.h) 的 `Limit_quote` 在不超过数量时全部打折、超出部分全价，10 件中 3 件折后合计 182。

## 15.8–15.10 静态与动态类型

变量的静态类型在编译期确定，引用/指针所指对象的动态类型在运行期才确定。`print_total(os, bulk, 10)` 形参静态类型是 `Quote`，动态类型是 `Bulk_quote`，虚调用按后者绑定。

## 15.11–15.14 debug 与覆盖

`debug()` 是虚函数，每层打印自己的数据并调用基类版本（15.11）。15.12：不需要显式 `virtual`——覆盖继承的虚函数自动是虚函数，但写上更清晰。15.13 的 `name()` 在派生类里写成 `this->name()` 后实际仍调用派生版本（无限递归），应为 `Base::name()`。15.14 中通过引用调用 `func1` 走动态绑定，`func2` 是非虚函数按静态类型。

## 15.15–15.17 Disc_quote 抽象基类

`Disc_quote` 把数量与折扣集中，`net_price` 声明为纯虚（`= 0`），类因此是抽象的——15.17 试图定义 `Disc_quote` 对象会编译失败；只能创建 `Bulk_quote`/`Limit_quote` 的对象。

## 15.18–15.22 继承访问与转换

[ex15_18_20.cpp](ex15_18_20.cpp) 保留合法转换、注释掉非法转换：public 继承可以转成基类指针，protected/private 继承的派生类指针不能转给基类；经 protected 链的孙类同样不行。15.21/15.22：选择 public/protected/private 的依据是"派生类是否是基类的一种"；`Disc_quote` 把共有数据提为 protected 成员。

## 15.23–15.27 对象切片与拷贝控制

`print_total_by_value` 按值接收 `Quote`，发生切片，`Bulk_quote` 也按基类规则计价（输出 200 而不是 160）。15.24/15.25：虚析构让 `delete base_ptr` 走完整析构链。[Quote.h](Quote.h) 的拷贝/移动全部打印踪迹（15.26/15.27）。

## 15.28–15.30 两种容器

[ex15_26_28_29.cpp](ex15_26_28_29.cpp)：`vector<Quote>` 存 `Bulk_quote` 时切片，10 件总价 200；`vector<shared_ptr<Quote>>` 保留动态类型，总价 160。[Basket.h](Basket.h) 用 multiset 按 ISBN 聚合，`add_item` 经虚 `clone()` 复制（15.30）；[ex15_30.cpp](ex15_30.cpp) 的购物篮输出四件、三组共 87.5。

## 15.31–15.33 Query 表达式的求值与拷贝

15.31：`Query("a") | Query("b") & ~Query("c")` 构造出 OrQuery(WordQuery(a), AndQuery(WordQuery(b), NotQuery(WordQuery(c))))。15.32：`shared_ptr` 共享底层对象，拷贝 Query 只复制指针；直接拷贝 Query_base 对象会拷贝整棵子树。15.33：虚析构保证经基类指针删除时逐层销毁。

## 15.34–15.41 Query 系统

[Query.h](Query.h) 实现全书最大的类族：`Query_base`（抽象）→ `WordQuery`、`NotQuery`、`BinaryQuery` → `OrQuery`/`AndQuery`。[TextQuery.h](TextQuery.h) 在 ch12 版本上给 `QueryResult` 增加了 `begin/end/get_file`。[ex15_39_41.cpp](ex15_39_41.cpp) 对 [ch12 的 story.txt](../ch12/data/story.txt) 运行五个查询：单词、`~(CMake)`（4 行）、`(CMake | file)`（5 行）、`(CMake & file)`（1 行）与组合表达式（4 行），输出与手工核对一致。15.40：两个词都不存在时 OrQuery 结果为空集，不报错。

## 15.42 查询的扩展

书中三个方向（带历史、按句子、带行号前缀）都在现有结构上扩展：保存表达式历史只需把 Query 压入容器；按句子需先按句号切分文件；行号打印已在 `print` 中实现，附加行号参数即可。作为示例，程序已把 rep() 与行号一并输出。

## 验证记录

本轮 5 个程序使用 CMake（NMake + MSVC 19.29、`cxx_std_11`、`/W4 /utf-8`）构建并全部运行：折扣规则、debug 链、切片对比、Basket 聚合计价与五个查询表达式均与题解一致。个人复习完成后再勾选 [复习提纲](REVIEW.md) 中的检查项。
