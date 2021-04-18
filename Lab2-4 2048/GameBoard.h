//
// Created by AAA on 2021/3/15.
//

#ifndef LAB1_GAMEBOARD_H
#define LAB1_GAMEBOARD_H

#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

class GameBoard {
    int boardSize = 4;
    vector <vector<int>> board;
    //node_num only modified in function generate_node() and function merge()
    int node_num = 0;
    //node_max only modified in function merge when a new biggest number appear
    int node_max = 2;

    string player_name[2];

    int player_score[2]{0, 0};
    int turn = 0;// 0表示玩家1,1表示玩家2
    int cheat_turn = 0;
    bool test_mode = false;
    bool multi_mode = false;
    bool cheat_mode = false;
    bool has_cheat = false;
    string cheat_content;

public:
    GameBoard();

    /*
     * Summary: let the game start
     */
    void start();

    void test_mode_on();

    void boardInit(int size);

private:
    /*
     * Summary: print the game board according to attribute board
     */
    void print();

    /*
     * Summary: use move_one on all numbers
     * Parameter:
     *     direction: how to move, also determine the order to move numbers
     * Return:
     *     true if at least one number moved
     */
    bool move(char direction);

    /*
     * Summary: use move_one on all numbers
     * Parameter:
     *     location_self: two ints represents the location of number
     *     direction: the direction to move
     * Return:
     *     true if the number is moved
     */
    bool move_one(int location_self[2], char direction);

    /*
     * Summary: use merge_one on all numbers
     * Parameter:
     *     direction: how to merge, also determine the order to merge numbers
     * Return:
     *     true if at least two numbers merged
     */
    bool merge(char direction);

    /*
     * Summary: try merge a number with its neighbor
     * Parameter:
     *     location_self: location of the moving number
     *     direction: the direction to merge
     * Return:
     *     true if successfully merged
     * */
    bool merge_one(const int location_self[2], char direction);

    /*
     * Summary: randomly generate a new number 2 in the board
     */
    void generate_node();

    /*
     * Summary: estimate whether the game is over
     * Return:
     *     true if no number could be moved
     *     when test_mode turned on, the game would be over if a number becomes 64
     * */
    bool is_over();

    /*
     * Summary: whether a location is out of the board
     * Parameter:
     *     row: row of location
     *     col: col of location
     * Return:
     *     true if the location is out(row or col not in [0,4))*/
    bool is_out(int row, int col);

    bool can_merge();

    char check_limited_move();

    //输入棋盘中的某行，查看是否有移动空间。移动方向默认为先输入的参数方向
    bool can_move_line(vector<int> line);
};


#endif //LAB1_GAMEBOARD_H
