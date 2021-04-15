#include <iostream>
#include <string>
#include "GameBoard.h"

using namespace std;

int main(int argc, char **argv) {
    GameBoard gameBoard;
    gameBoard.boardInit(4);
    for (int i = 0; i < argc; ++i) {
        string test_mode = "-t";
        string size_change = "-s";
        if (test_mode == (argv[i])) {
            cout << "测试模式-游戏目标为合成出64" << endl;
            gameBoard.test_mode_on();
        } else if (size_change == (argv[i])) {
            if (i + 1 < argc) {
                // 没有检测参数长度 输入3b将被认可为3
                char size = argv[i + 1][0];
                size -= '0';
                if (size > 5 or size < 3) {
                    cout << "-s 参数需要是3-5的数字" << endl;
                    exit(0);
                } else {
                    gameBoard.boardInit(size);
                }
            }
        }
    }
    gameBoard.start();
}