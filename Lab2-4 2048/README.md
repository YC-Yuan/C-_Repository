# Lab2

C++实现控制台2048

19302010020 袁逸聪

## 编译运行环境

Windows10 Ubuntu20.04

编译器版本-gcc 9.3.0

## 编译运行指南

### windows10

1. 用命令行cd到当前目录下
2. $ g++ main.cpp GameBoard.cpp
3. 将编译出a.exe文件
4. $ a.exe 或 $ a.exe

### ubuntu20.04

1. cd到当前目录下
2. $ g++ main.cpp GameBoard.cpp
3. 将编译出a.out文件
4. $ ./a.out 或 $ ./a.out

### 命令行参数说明

-t 为测试模式，合成出64后游戏结束
-s [int] 为大小设置，可输入2-5的整数改变棋盘大小

>作弊模式在游玩时输入"c [作弊指令]"或"C [作弊指令]"开启，2×2棋盘下较容易触发条件
