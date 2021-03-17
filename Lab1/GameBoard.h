//
// Created by AAA on 2021/3/15.
//

#ifndef LAB1_GAMEBOARD_H
#define LAB1_GAMEBOARD_H

#include <string>

using namespace std;

class GameBoard {
    bool test_mode;
    int board[4][4]{};
    int node_num;
    int node_max;
    int score;

public:
    GameBoard();

    void start();

private:
    void print();

    void move(const string &para);

    void generate_node();

    void is_over();
};


#endif //LAB1_GAMEBOARD_H
