//
// Created by AAA on 2021/3/15.
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include "GameBoard.h"

using namespace std;

GameBoard::GameBoard() {
    test_mode = false;
    node_num = 0;
    node_max = 2;
    score = 0;
    for (auto &i : board) {
        for (int &j : i) {
            j = 0;
        }
    }
    generate_node();
}

void GameBoard::start() {
    print();
    while (true) {
        char direction;
        cin >> direction;
        if (direction == 'U') move(direction);
        generate_node();
        print();
    }

}

void GameBoard::generate_node() {
    if (node_num == 16) {
        cout << "棋盘满了，不应该再生成新数字！" << endl;
    }
    srand(time(nullptr));
    bool is_set = false;
    while (!is_set) {
        int random_row = rand() % 4;
        int random_col = rand() % 4;
        if (board[random_row][random_col] == 0) {
            board[random_row][random_col] = 2;
            node_num++;
            is_set = true;
        }
    }
}

void GameBoard::is_over() {

}

void GameBoard::print() {
    char border[] = "+-----+-----+-----+-----+";
    char split = '|';
    cout << border << endl;
    cout << split << setw(5) << board[0][0];
    cout << split << setw(5) << board[0][1];
    cout << split << setw(5) << board[0][2];
    cout << split << setw(5) << board[0][3] << split << endl;
    cout << border << endl;
    cout << split << setw(5) << board[1][0];
    cout << split << setw(5) << board[1][1];
    cout << split << setw(5) << board[1][2];
    cout << split << setw(5) << board[1][3] << split << endl;
    cout << border << endl;
    cout << split << setw(5) << board[2][0];
    cout << split << setw(5) << board[2][1];
    cout << split << setw(5) << board[2][2];
    cout << split << setw(5) << board[2][3] << split << endl;
    cout << border << endl;
    cout << split << setw(5) << board[3][0];
    cout << split << setw(5) << board[3][1];
    cout << split << setw(5) << board[3][2];
    cout << split << setw(5) << board[3][3] << split << endl;
    cout << border << endl;
}

bool GameBoard::merge(const int *location_self, const int *location_target) {
    cout << "before merge" << endl;
    print();
    cout << "self:" << location_self[0] << location_self[1] << endl;
    cout << "target:" << location_target[0] << location_target[1] << endl;

    int self_row = location_self[0];
    int self_col = location_self[1];
    int target_row = location_target[0];
    int target_col = location_target[1];
    bool is_merged = board[target_row][target_col] != 0;
    board[target_row][target_col] += board[self_row][self_col];
    node_max = max(node_max, board[target_row][target_col]);
    board[self_row][self_col] = 0;
    cout << "after merge" << endl;
    print();
    return is_merged;
}

void GameBoard::move(char direction) {
    switch (direction) {
        case 'U':
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    int location_self[2] = {i, j};
                    move_one(location_self, direction);
                }
            }
            break;
        case 'D':
            break;
        case 'L':
            break;
        case 'R':
            break;
    }
}

void GameBoard::move_one(int *location_self, char direction) {
    int self_row = location_self[0];
    int self_col = location_self[1];
    if (board[self_row][self_col] == 0) return;
    int target_row = self_row;
    int target_col = self_col;
    switch (direction) {
        case 'U':
            target_row--;
            while (target_row >= 0) {
                if (board[target_row][target_col] != 0 && board[target_row][target_col] != board[self_row][self_col]) {
                    break;
                }
                int location_target[2] = {target_row, target_col};
                merge(location_self, location_target);
                location_self[0] --;
                target_row--;
            }
            break;
        case 'D':
            break;
        case 'L':
            break;
        case 'R':
            break;
    }
}