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
            cout << "����ģʽ-��ϷĿ��Ϊ�ϳɳ�64" << endl;
            gameBoard.test_mode_on();
        } else if (size_change == (argv[i])) {
            if (i + 1 < argc) {
                // û�м��������� ����3b�����Ͽ�Ϊ3
                char size = argv[i + 1][0];
                size -= '0';
                if (size > 5 or size < 3) {
                    cout << "-s ������Ҫ��3-5������" << endl;
                    exit(0);
                } else {
                    gameBoard.boardInit(size);
                }
            }
        }
    }
    gameBoard.start();
}