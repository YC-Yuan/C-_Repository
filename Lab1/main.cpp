#include <iostream>
#include <string>

#include "GameBoard.h"


using namespace std;

int main(int argc, char **argv) {
    GameBoard gameBoard;
    for (int i = 0; i < argc; ++i) {
        string test_mode = "-t";
        if (test_mode == (argv[i])) {
            cout << "测试模式，第一个64出现时游戏即结束" << endl;
            gameBoard.test_mode_on();
        }
    }
    gameBoard.start();
}