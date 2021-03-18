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
    //node_num only modified in function generate_node() and function merge()
    node_num = 0;
    //node_max only modified in function merge when a new biggest number appear
    node_max = 2;
    score = 0;
    for (auto &i : board) {
        for (int &j : i) {
            j = 0;
        }
    }
    //this will set node_num to 1
    generate_node();
}

void GameBoard::start() {
    print();
    while (!is_over()) {
        char direction;
        cin >> direction;
        if (direction == 'W' or direction == 'S' or direction == 'A' or direction == 'D') {
            if (move(direction)) {
                generate_node();
            }
        } else {
            cout << "无效输入，请使用U D L R表示上下左右" << endl;
        }
        print();
        cout << "num：" << node_num << endl;
        cout << "max:" << node_max << endl;
    }
    cout << "游戏结束！" << endl;
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

bool GameBoard::is_over() {
    // test_mode condition
    if (test_mode) {
        if (node_max >= 64) {
            return true;
        }
    }

    // can move or not
    if (node_num <= 16) { return false; }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == board[i + 1][j] || board[i][j] == board[i][j + 1]) { return false; }
        }
    }
    if (board[3][3] == board[2][3]) return false;
    if (board[3][3] == board[3][2]) return false;
    return true;
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


bool GameBoard::move(char direction) {
    bool is_moved = false;
    switch (direction) {
        case 'W':
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    int location_self[2] = {i, j};
                    if (move_one(location_self, direction)) {
                        is_moved = true;
                    }
                }
            }
            break;
        case 'S':
            for (int i = 3; i >= 0; --i) {
                for (int j = 0; j < 4; ++j) {
                    int location_self[2] = {i, j};
                    if (move_one(location_self, direction)) {
                        is_moved = true;
                    }
                }
            }
            break;
        case 'A':
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    int location_self[2] = {j, i};
                    if (move_one(location_self, direction)) {
                        is_moved = true;
                    }
                }
            }
            break;
        case 'D':
            for (int i = 3; i >= 0; --i) {
                for (int j = 0; j < 4; ++j) {
                    int location_self[2] = {j, i};
                    if (move_one(location_self, direction)) {
                        is_moved = true;
                    }
                }
            }
            break;
    }
    return is_moved;
}

bool GameBoard::move_one(int *location_self, char direction) {
    bool is_moved = false;
    location_self[0];
    location_self[1];
    if (board[location_self[0]][location_self[1]] == 0) return is_moved;
    int target_row = location_self[0];
    int target_col = location_self[1];
    //decide target according to direction
    switch (direction) {
        case 'W':
            target_row--;
            break;
        case 'S':
            target_row++;
            break;
        case 'A':
            target_col--;
            break;
        case 'D':
            target_col++;
            break;
    }
    while (target_row >= 0 && target_row < 4 && target_col < 4 && target_col >= 0) {
        if (board[target_row][target_col] != 0 &&
            board[target_row][target_col] != board[location_self[0]][location_self[1]]) {
            break;
        }
        int location_target[2] = {target_row, target_col};
        is_moved = true;
        if (merge(location_self, location_target)) { break; }
        //complete movement after merge and decide new target
        switch (direction) {
            case 'W':
                location_self[0]--;
                target_row--;
                break;
            case 'S':
                location_self[0]++;
                target_row++;
                break;
            case 'A':
                location_self[1]--;
                target_col--;
                break;
            case 'D':
                location_self[1]++;
                target_col++;
                break;
        }
    }
    return is_moved;
}

bool GameBoard::merge(const int *location_self, const int *location_target) {
    bool is_merged = false;
//    cout << "before merge" << endl;
//    print();
//    cout << "self:" << location_self[0] << location_self[1] << endl;
//    cout << "target:" << location_target[0] << location_target[1] << endl;
    int self_row = location_self[0];
    int self_col = location_self[1];
    int target_row = location_target[0];
    int target_col = location_target[1];
    if (board[target_row][target_col] != 0) {
        is_merged = true;
        node_num--;
    }
    board[target_row][target_col] += board[self_row][self_col];
    node_max = max(node_max, board[target_row][target_col]);
    board[self_row][self_col] = 0;
//    cout << "after merge" << endl;
//    print();
    return is_merged;
}

void GameBoard::test_mode_on() {
    test_mode = true;

}
