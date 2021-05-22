# OOP Lab6 说明文档

19302010020 袁逸聪

## 编译指南

>g++ main.cpp GameBoard.cpp Player.cpp CheatModule.cpp

需要在UTF-8的命令行运行否则会有中文乱码

## 参数说明

-t 开启测试模式，合成出64就结束游戏

-s [int] 设置棋盘大小，需要在2-5之间

-i [filename] 设置输入文件

-o [filename] 设置输出文件

输入输出文件同时设置才会触发输出功能

输入输出功能与游戏进程不冲突，程序将在完成输出后开启游戏（-t -s参数也是有效的）
