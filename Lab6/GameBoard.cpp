//
// Created by WaiWaiXi on 2021/5/21.
//

#include "GameBoard.h"

GameBoard::GameBoard() = default;

// 游戏流程控制
void GameBoard::start() {

}

void GameBoard::test_mode_on() {
    this->test_mode = true;
}

void GameBoard::board_init(int size) {
    this->board.resize(size);
    for (auto &item : board) {
        item.resize(size);
        for (auto &number : item)
            number = 0;
    }
}

void GameBoard::players_init(int size) {
    this->playerNumber = size;
    this->players = vector<Player>(size);
}

void GameBoard::generate_node() {
    if (this->node_num == this->boardSize * this->boardSize) {
        cout << "棋盘满了，不应该再生成新数字！" << endl;
    }
    srand(time(nullptr));
    while (true) {
        int row = rand() % this->boardSize;
        int col = rand() % this->boardSize;
        if (this->board[row][col] == 0) {
            this->board[row][col] = 2;
            this->node_num++;
            break;
        }
    }
}
