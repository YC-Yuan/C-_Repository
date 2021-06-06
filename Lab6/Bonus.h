//
// Created by AAA on 2021/6/6.
//

#ifndef LAB6_BONUS_H
#define LAB6_BONUS_H

#include "Log.h"
#include "chrono"
#include "ctime"

static auto pre_time = std::chrono::steady_clock::now();
static Log log;

class Bonus {
public:
    // 跟内部的时间做比较，更新时间，如果间隔小则进行日志输出。返回值为奖励得分，0为不奖励
    int check_bonus(const string &player_name) const;

    Bonus();

    explicit Bonus(string prefix);

    int bonus = 1;
private:
    bool log_mode = false;
};


#endif //LAB6_BONUS_H
