//
// Created by WaiWaiXi on 2021/5/21.
//

#ifndef LAB6_GAMEBOARD_H
#define LAB6_GAMEBOARD_H

#include "Player.h"
#include "CheatModule.h"
#include "vector"
#include "iostream"
#include "ctime"

using namespace std;

class GameBoard {
    // 默认棋盘大小
    int boardSize = 4;
    // 棋盘数组，记录分数
    vector<vector<int>> board;
    // 当前数字数目
    int node_num = 0;
    // 数字最大分数
    int node_max = 2;

    // 默认玩家数量,直接表征单人、多人模式
    int playerNumber = 1;
    vector<Player> players;
    int turn = 0;

    // 测试模式，node_max达到64就结束
    bool test_mode = false;

    // 作弊码模块
    CheatModule cheat;

public:
    GameBoard();

    void start();

    void test_mode_on();

    void board_init(int size);

    void players_init(int size);

private:
    // 生成新node
    void generate_node();

    bool is_over();

    // 打印当前玩家信息
    void print_player(vector<Player> players, int turn);

    // 打印棋盘
    void print_board();

    // 打印当前玩家分数
    void print_score(vector<Player> players, int turn);

    // 棋盘朝某个方向移动
    vector<vector<int>> move(vector<vector<int>> board, char direction);

    // 棋盘朝某方向合并
    vector<vector<int>> merge(vector<vector<int>> board, char direction);
};


#endif //LAB6_GAMEBOARD_H
