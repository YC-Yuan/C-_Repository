//
// Created by WaiWaiXi on 2021/5/21.
//

#ifndef LAB6_GAMEBOARD_H
#define LAB6_GAMEBOARD_H

#include "Player.h"
#include "CheatModule.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
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
    int test_max_node = 64;

    // 作弊码模块
    CheatModule cheat;

public:
    GameBoard();

    void test(const string &in_name, const string &out_name);

    void start();

    void test_mode_on();

    void board_init(int size);

    void players_init(int size);

private:
    // 生成新node
    vector<int> generate_node();

    bool is_over();

    // 打印当前玩家信息
    static void print_player(vector<Player> players, int turn);

    // 打印棋盘
    void print_board();

    // 打印当前玩家分数
    static void print_score(vector<Player> players, int turn);

    // 棋盘接受指令：移动+合并+移动
    vector<vector<int>> play(vector<vector<int>> origin_board, char direction, bool real);

    // 检测指令是否有效
    bool can_play(const vector<vector<int>> &origin_board, char direction);

    // 棋盘朝某个方向移动
    static vector<vector<int>> move(vector<vector<int>> origin_board, char direction);

    static vector<vector<int>> move_left(vector<vector<int>> origin_board);

    static vector<int> move_line_left(vector<int> origin_line);

    // 将期盼顺时针转动90度
    static vector<vector<int>> rotate(vector<vector<int>> origin_board);

    // 棋盘朝某方向合并
    vector<vector<int>> merge(vector<vector<int>> origin_board, char direction, bool real);

    vector<vector<int>> merge_left(vector<vector<int>> origin_board, bool real);

    vector<int> merge_line_left(vector<int> origin_line, bool real);

    static bool is_different(vector<vector<int>> board_i, vector<vector<int>> board_j);

};


#endif //LAB6_GAMEBOARD_H
