# C++ Primer 第五版：习题与复习笔记

重新整理全部课后习题，已完成第 2–12 章。采用“先整理题解，再边看边练”的方式。

教材：项目根目录的《C++ Primer 中文版（第五版）》扫描 PDF。笔记中的“书页”是印刷页码，“PDF 页”是阅读器从 1 开始的页面序号。

## 阅读入口

- [第一章：开始（1.1–1.25 完整题解）](ch01/README.md)
- [第二章：变量和基本类型（2.1–2.42）](ch02/README.md)
- [第三章：字符串、向量和数组（3.1–3.42）](ch03/README.md)
- [第四章：表达式（4.1–4.35）](ch04/README.md)
- [第五章：语句（5.1–5.25）](ch05/README.md)
- [第六章：函数（6.1–6.56）](ch06/README.md)
- [第七章：类（7.1–7.58）](ch07/README.md)
- [第八章：IO 库（8.1–8.14）](ch08/README.md)
- [第九章：顺序容器（9.1–9.52）](ch09/README.md)
- [第十章：泛型算法（10.1–10.42）](ch10/README.md)
- [第十一章：关联容器（11.1–11.38）](ch11/README.md)
- [第十二章：动态内存（12.1–12.32）](ch12/README.md)
- [第十三章：拷贝控制（13.1–13.58）](ch13/README.md)
- [第十四章：重载运算与类型转换（14.1–14.54）](ch14/README.md)
- [第十五章：面向对象程序设计（15.1–15.43）](ch15/README.md)
- [第十六章：模板与泛型编程（16.1–16.68）](ch16/README.md)
- [第十七章：标准库特殊设施（17.1–17.40）](ch17/README.md)
- [第十八章：用于大型程序的工具（18.1–18.32）](ch18/README.md)
- [第十九章：特殊工具与技术（19.1–19.28）](ch19/README.md)
- [全书进度](PROGRESS.md)

## 整理约定

- 每章用 `chXX/README.md` 汇总题意摘要、思路、答案、样例和易错点。
- 编程题用独立的 `ex1_01.cpp` 等文件保存；每个程序单独编译，避免多个 `main` 冲突。
- 以本书采用的 C++11 为学习基线；必要的环境差异另行说明。
- “题解已整理”“代码已验证”和“自己已掌握”分别记录，不用阅读进度代替练习进度。
- 原有 `chXX` 文件和 `Primer_CH06` 笔记保留，后续到对应章节时再核对、吸收。

## 编译各章

原项目使用 CLion + CMake。每个章节目录（`ch01`–`ch19`）都有独立的 `CMakeLists.txt`，
根目录也提供了统一入口。可在 CLion 中打开根目录或任一 `chXX` 目录，
也可在已配置编译器的终端运行：

```powershell
cmake -S chXX -B build/chXX
cmake --build build/chXX --config Debug
```

可执行文件的位置取决于生成器：例如 Visual Studio 通常在 `build/chXX/Debug`，NMake、Ninja 等单配置生成器通常直接放在 `build/chXX`。部分程序需要命令行参数或数据文件，用法见对应章节的 README。

### 在 VS Code 中运行（Windows + MSVC）

用“打开文件夹”打开项目根目录，安装 Microsoft 的 C/C++ 和 CMake Tools 扩展。
仓库已配置由 CMake Tools 提供 IntelliSense 编译参数，不需要手动填写标准库的 `includePath`。

首次使用时：

1. 按 `Ctrl+Shift+P`，执行 `CMake: Select a Kit`，选择已安装的 MSVC x64 工具链。
2. 执行 `CMake: Configure`，等待配置完成。
3. 在 CMake 侧栏的 Launch 项中选择习题目标，例如 `ex19_09_10`。
4. 在“运行和调试”中选择 `CMake: Run selected exercise (MSVC)`。
   按 `Ctrl+F5` 运行，或按 `F5` 启动断点调试；运行前会自动构建所选目标。

后续运行可直接按 `Ctrl+F5`；换题时先切换 CMake 的 Launch 目标。
运行的是所选目标，不会随当前编辑的文件自动切换。也可直接点击 CMake 侧栏 Launch 旁的运行按钮。
输入和输出显示在终端中。需要命令行参数的习题可修改 `.vscode/launch.json` 的 `args`；
默认工作目录为项目根目录，数据文件路径请按各章 README 填写。

如果头文件红线仍未消失，先确认 CMake 配置成功，再执行 `Developer: Reload Window`。
