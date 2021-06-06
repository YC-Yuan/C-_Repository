//
// Created by AAA on 2021/6/6.
//

#include "Bonus.h"

bool Bonus::check_bonus() {

}

string DoubleToString(const double value, unsigned int precision) {
    std::ostringstream out;
    if (precision > 0)
        out.precision(precision);

    out << value;
    return out.str();
}

bool Bonus::check_bonus(string player_name) {
    bool result = false;
    auto time = std::chrono::steady_clock::now();
    int mills = std::chrono::duration<double, std::milli>(time - pre_time).count();
    if (mills < 1000) {
        // 一秒内作出反应，奖励！
        double time_use = (double) mills / 1000;
        string time_str = DoubleToString(time_use, 2);

        // 日记
        log.log(player_name, time_str, bonus);
        result = true;
    } else {
        pre_time = time;
    }
    return result;
}

