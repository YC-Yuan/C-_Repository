//
// Created by AAA on 2021/6/6.
//

#include "Bonus.h"

#include <utility>
#include <iostream>

// 将double保留小数点后两位转化为字符串
string DoubleToString(const double value, unsigned int precision) {
    std::ostringstream out;
    if (precision > 0)
        out.precision(precision);

    out << value;
    return out.str();
}

int Bonus::check_bonus(const string &player_name) const {
    int result = 0;
    auto time = std::chrono::steady_clock::now();
    int mills = std::chrono::duration<double, std::milli>(time - pre_time).count();
    if (mills < 1000) {
        // 一秒内作出反应，奖励！
        double time_use = (double) mills / 1000;
        string time_str = DoubleToString(time_use, 2);

        // 日记
        if (log_mode) {
            cout << "bonus正在调用log：：：：：" << endl;
            log.log(player_name, time_str, bonus);
        }
        result = bonus;
    } else {
        pre_time = time;
    }
    return result;
}

Bonus::Bonus(string prefix) {
    log_mode = true;
    log = Log(move(prefix));
}

Bonus::Bonus() = default;
