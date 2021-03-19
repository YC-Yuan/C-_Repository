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

    /*
     * Summary: let the game start
     */
    void start();

    void test_mode_on();

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
};


#endif //LAB1_GAMEBOARD_H