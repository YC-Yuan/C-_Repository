//
// Created by AAA on 2021/3/15.
//

#include <random>
#include <ctime>
#include "GameBoard.h"

using namespace std;

GameBoard::GameBoard() {
    test_mode = false;
    node_num = 1;
    node_max = 2;
    score = 0;

    for (auto &i : board) {
        for (int &j : i) {
            j = 0;
        }
    }
}

void GameBoard::start() {

}

void GameBoard::move(const string &para) {

}

void GameBoard::generate_node() {
    srand(time(nullptr));
    int random_index = rand() % 16;

}

void GameBoard::is_over() {

}

void GameBoard::print() {

}
