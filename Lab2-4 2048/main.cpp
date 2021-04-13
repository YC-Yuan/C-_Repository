#include <iostream>
#include <string>

#include "GameBoard.h"


using namespace std;

int main(int argc, char **argv) {
    GameBoard gameBoard;
    for (int i = 0; i < argc; ++i) {
        string test_mode = "-t";
        if (test_mode == (argv[i])) {
            cout << "test_mode on" << endl;
            gameBoard.test_mode_on();
        }
    }
    gameBoard.start();
}