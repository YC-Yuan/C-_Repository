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
     * Summary: let all the numbers move, call function move() inside
     * Parameter:
     *     direction: the direction to move, valid inputs are 'W' 'S' 'A' 'D'
     *                also determine the order to move numbers
     * Return:
     *     true if at least one number is moved
     */
    bool move(char direction);

    /*
     * Summary: let one number move toward a direction until it cannot move any more
     * Parameter:
     *     location_self: two ints represents the location of number
     *     direction: the direction to move
     * Return:
     *     true if the number is moved
     */
    bool move_one(int location_self[2], char direction);

    /*
     * Summary: add one number to another and set the first one to zero
     * Parameter:
     *     location_self: two ints represents the location of the moving number
     *     location_target: two ints represents the location of the target number
     * Return:
     *     true if there are two non-zero numbers merged
     *     false if we just move a number to a zero ground
     */
    bool merge(const int location_self[2], const int location_target[2]);

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
};


#endif //LAB1_GAMEBOARD_H
