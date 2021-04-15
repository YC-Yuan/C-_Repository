//
// Created by AAA on 2021/3/15.
//

#include "GameBoard.h"

using namespace std;

GameBoard::GameBoard() = default;

void GameBoard::boardInit(int size) {
    boardSize = size;
    this->board.resize(boardSize);
    for (auto &i : board) {
        i.resize(boardSize);
        for (int &j : i) {
            j = 0;
        }
    }
    //this will set node_num to 1
    generate_node();
}

void GameBoard::start() {
    cout << "请进行模式选择" << endl;
    cout << "1:单人模式" << endl;
    cout << "2:双人模式" << endl;
    cout << "请输入对应的模式序号" << endl;
    while (true) {
        string mode;
        cin >> mode;
        if (mode == "1") {
            string name;
            cout << "请玩家输入名称:" << endl;
            cin >> name;
            player_name[0] = name;
            break;
        } else if (mode == "2") {
            multi_mode = true;
            string name;
            cout << "请玩家一输入名称:" << endl;
            cin >> name;
            player_name[0] = name;
            cout << "请玩家二输入名称:" << endl;
            cin >> name;
            player_name[1] = name;
            break;
        } else {
            cout << "请输入1或2选择模式" << endl;
        }
    }
    print();
    cout << "输入 W S A D 表示上下左右，以回车确定" << endl;

    while (true) {
        string direction;
        cin >> direction;
        if (direction == "W" or direction == "S" or direction == "A" or direction == "D") {
            bool is_moved = move(direction[0]);
            bool is_merged = merge(direction[0]);
            move(direction[0]);
            bool is_changed = is_merged or is_moved;
            if (is_changed) {
                generate_node();
                if (is_over()) { break; }
                cout << player_name[turn] << "当前分数为:" << player_score[turn] << endl;
                if (multi_mode) {// change player
                    turn = (turn + 1) % 2;
                    cout << "请" << player_name[turn] << "进行操作" << endl;
                }
            }
        } else {
            cout << "无效输入，请使用 W S A D 表示上下左右" << endl;
        }
        print();
    }
    if (multi_mode) {
        cout << player_name[0] << "当前分数为:" << player_score[0] << endl;
        cout << player_name[1] << "当前分数为:" << player_score[1] << endl;
        if (player_score[0] == player_score[1]) { cout << "打成平局!" << endl; }
        else {
            int winner = 0;
            if (player_score[0] < player_score[1]) { winner = 1; }
            cout << "胜利者为" << player_name[winner] << endl;
        }
    } else {
        cout << player_name[turn] << "最终分数为:" << player_score[turn] << endl;
    }

    cout << "最大方块达到" << node_max << ",游戏结束！" << endl;
}

void GameBoard::generate_node() {
    if (node_num == 16) {
        cout << "棋盘满了，不应该再生成新数字！" << endl;
    }
    srand(time(nullptr));
    bool is_set = false;
    while (!is_set) {
        int random_row = rand() % boardSize;
        int random_col = rand() % boardSize;
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
    int node_max_num = boardSize * boardSize;
    if (node_num <= node_max_num) { return false; }

    int smallSize = boardSize - 1;
    // 对左上角(boardSize-1)*(boardSize-1)的方阵，检测其与右、下是否可合并
    for (int i = 0; i < smallSize; ++i) {
        for (int j = 0; j < smallSize; ++j) {
            if (board[i][j] == board[i + 1][j] || board[i][j] == board[i][j + 1]) { return false; }
        }
    }
    //对最下行和最右列，检测其内部的是否可合并
    for (int i = 0; i < smallSize; ++i) {
        if (board[smallSize][i] == board[smallSize][i + 1] ||
            board[i][smallSize] == board[i + 1][smallSize]) { return false; }
    }
    return true;
}

void GameBoard::print() {
    char split = '|';
    string border = "+";

    for (int i = 0; i < boardSize; i++) {
        border.append("-----+");
    }
    for (int i = 0; i < boardSize; i++) {
        cout << border << endl;
        for (int j = 0; j < boardSize; j++) {
            cout << split << setw(5) << board[i][j];
        }
        cout << split << endl;
    }
    cout << border << endl;
}


bool GameBoard::move(char direction) {
    bool is_moved = false;
    switch (direction) {
        case 'W':
            for (int i = 0; i < boardSize; ++i) {
                for (int j = 0; j < boardSize; ++j) {
                    int location_self[2] = {i, j};
                    if (move_one(location_self, direction)) {
                        is_moved = true;
                    }
                }
            }
            break;
        case 'S':
            for (int i = 3; i >= 0; --i) {
                for (int j = 0; j < boardSize; ++j) {
                    int location_self[2] = {i, j};
                    if (move_one(location_self, direction)) {
                        is_moved = true;
                    }
                }
            }
            break;
        case 'A':
            for (int i = 0; i < boardSize; ++i) {
                for (int j = 0; j < boardSize; ++j) {
                    int location_self[2] = {j, i};
                    if (move_one(location_self, direction)) {
                        is_moved = true;
                    }
                }
            }
            break;
        case 'D':
            for (int i = 3; i >= 0; --i) {
                for (int j = 0; j < boardSize; ++j) {
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
        if (board[self_row][self_col] == 0) { break; }
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
            for (int i = 0; i < boardSize; ++i) {
                for (int j = 0; j < boardSize; ++j) {
                    int location_self[2] = {i, j};
                    if (merge_one(location_self, direction)) {
                        is_merged = true;
                    }
                }
            }
            break;
        case 'S':
            for (int i = 3; i >= 0; --i) {
                for (int j = 0; j < boardSize; ++j) {
                    int location_self[2] = {i, j};
                    if (merge_one(location_self, direction)) {
                        is_merged = true;
                    }
                }
            }
            break;
        case 'A':
            for (int i = 0; i < boardSize; ++i) {
                for (int j = 0; j < boardSize; ++j) {
                    int location_self[2] = {j, i};
                    if (merge_one(location_self, direction)) {
                        is_merged = true;
                    }
                }
            }
            break;
        case 'D':
            for (int i = 3; i >= 0; --i) {
                for (int j = 0; j < boardSize; ++j) {
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
        player_score[turn] += board[target_row][target_col];
    }
    return is_merged;
}

void GameBoard::test_mode_on() {
    test_mode = true;

}

bool GameBoard::is_out(int row, int col) {
    if (row > boardSize - 1 or row < 0) return true;
    if (col > boardSize - 1 or col < 0) return true;
    return false;
}
