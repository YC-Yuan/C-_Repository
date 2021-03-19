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
    cout << "����WSAD��ʾ�������ң��س���ȷ��" << endl;
    print();
    while (!is_over()) {
        char direction;
        cin >> direction;
        if (direction == 'W' or direction == 'S' or direction == 'A' or direction == 'D') {
            int is_changed = move(direction);
            is_changed = merge(direction) or is_changed;
            move(direction);
            if (is_changed) {
                generate_node();
            }
        } else {
            cout << "��Ч���룬��ʹ��U D L R��ʾ��������" << endl;
        }
        print();
//        cout << "num��" << node_num << endl;
//        cout << "max:" << node_max << endl;
    }
    cout << "��Ϸ������" << endl;
}

void GameBoard::generate_node() {
    if (node_num == 16) {
        cout << "�������ˣ���Ӧ�������������֣�" << endl;
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
    do {
        int self_row = location_self[0];
        int self_col = location_self[1];
        int target_row = self_row;
        int target_col = self_col;
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
        if (is_out(target_row, target_col) or board[target_row][target_col] != 0) {
            break;
        } else {
            board[target_row][target_col] = board[self_row][self_col];
            board[self_row][self_col] = 0;
            is_moved = true;
            location_self[0] = target_row;
            location_self[1] = target_col;
        }
    } while (true);
    return is_moved;
}

bool GameBoard::merge(char direction) {
    bool is_merged = false;
    switch (direction) {
        case 'W':
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    int location_self[2] = {i, j};
                    if (merge_one(location_self, direction)) {
                        is_merged = true;
                    }
                }
            }
            break;
        case 'S':
            for (int i = 3; i >= 0; --i) {
                for (int j = 0; j < 4; ++j) {
                    int location_self[2] = {i, j};
                    if (merge_one(location_self, direction)) {
                        is_merged = true;
                    }
                }
            }
            break;
        case 'A':
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    int location_self[2] = {j, i};
                    if (merge_one(location_self, direction)) {
                        is_merged = true;
                    }
                }
            }
            break;
        case 'D':
            for (int i = 3; i >= 0; --i) {
                for (int j = 0; j < 4; ++j) {
                    int location_self[2] = {j, i};
                    if (merge_one(location_self, direction)) {
                        is_merged = true;
                    }
                }
            }
            break;
    }
    return is_merged;
}

bool GameBoard::merge_one(const int *location_self, char direction) {
    bool is_merged = false;
    int self_row = location_self[0];
    int self_col = location_self[1];
    if (board[self_row][self_col] == 0) { return false; }
    int target_row = self_row;
    int target_col = self_col;
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
    if (is_out(target_row, target_col)) { return false; }
    if (board[self_row][self_col] == board[target_row][target_col]) {
        board[target_row][target_col] *= 2;
        board[self_row][self_col] = 0;
        node_max = max(node_max, board[target_row][target_col]);
        node_num--;
        is_merged = true;
    }
    return is_merged;
}

void GameBoard::test_mode_on() {
    test_mode = true;

}

bool GameBoard::is_out(int row, int col) {
    if (row > 3 or row < 0) return true;
    if (col > 3 or col < 0) return true;
    return false;
}
