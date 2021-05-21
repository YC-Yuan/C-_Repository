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

vector<vector<int>> GameBoard::move(vector<vector<int>> origin_board, char direction) {


    return vector<vector<int>>();
}

vector<vector<int>> GameBoard::move_left(vector<vector<int>> origin_board) {
    for (auto &i : origin_board) {
        i = move_line_left(i);
    }
    return origin_board;
}

vector<int> GameBoard::move_line_left(vector<int> origin_line) {
    int currIndex = 0;
    for (const auto &item : origin_line) {
        if (item != 0) {
            origin_line[currIndex] = item;
            currIndex++;
        }
    }
    for (int i = currIndex; i < origin_line.size(); ++i) {
        origin_line[i] = 0;
    }
    return origin_line;
}

void GameBoard::test() {
    vector<vector<int>> board = {{0, 1, 1, 1},
                                 {1, 2, 0, 3},
                                 {1, 2, 4, 5},
                                 {0, 0, 0, 0}};

    for (const auto &item : board) {
        for (const auto &i : item) {
            cout << i;
        }
        cout << endl;
    }

    board = move_left(board);


    for (const auto &item : board) {
        for (const auto &i : item) {
            cout << i;
        }
        cout << endl;
    }
}

