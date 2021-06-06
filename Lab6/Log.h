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

static ofstream out;

class Log {
    string prefix;
public:
    static void init();

    Log();

    explicit Log(string prefix);

    void log(const string &name, const string &direction, int score);

    void close();

private:
    static string get_time_string();
};


#endif //LAB6_LOG_H
