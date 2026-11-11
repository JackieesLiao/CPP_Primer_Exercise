# 第 12 章复习提纲

结合 [第 12 章习题](README.md) 使用；本文件用于检查知识点，勾选应留给自己实际练习后完成。

| 工具 | 典型用途 | 易错 |
| --- | --- | --- |
| `shared_ptr` | 多个使用者共享对象 | 不要用 `get()` 的结果再构造智能指针 |
| `unique_ptr` | 独占所有权 | 不可拷贝，只能 `release`/`reset` 转移 |
| `weak_ptr` | 打破循环、观察共享对象 | 使用前必须 `lock` |
| `new[]`/`delete[]` | 裸数组 | 配对使用 `delete[]`，未知数量需自行扩容 |
| 动态数组智能指针 | `unique_ptr<T[]>`、`shared_ptr` + 删除器 | `shared_ptr<T[]>` 是 C++17 特性 |

## 自测

- [ ] 解释 StrBlob 拷贝后两个对象共享哪些内容。
- [ ] 说出 `process(shared_ptr<int>(p.get()))` 为什么危险。
- [ ] 用 `weak_ptr` 重写一个迭代器类并说明 `lock` 的时机。
- [ ] 区分 `delete p` 与 `delete[] p` 的使用场景。
- [ ] 画出 TextQuery 与 QueryResult 的共享数据关系。
