//
// Created by AAA on 2021/6/6.
//

#ifndef LAB6_LOG_H
#define LAB6_LOG_H

#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "Player.h"

using namespace std;

class Log {
    ofstream out;
    string prefix;
public:
    Log(const string &file_path, string prefix);

    void log(const string &name, const string &direction, int score);

    void close();

private:
    static string get_time_string();
};


#endif //LAB6_LOG_H
