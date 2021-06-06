//
// Created by AAA on 2021/6/6.
//



#include <iostream>
#include <utility>
#include "Log.h"

void Log::close() {
    out.close();
}

string Log::get_time_string() {
    auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
    //转为字符串
    stringstream ss;
    ss << put_time(localtime(&t), "%Y/%m/%d/%H:%M:%S");
    string str_time = ss.str();
    return str_time;
}

void Log::log(const string &name, const string &direction, int score) {
    this->out << prefix << name << ' ' << get_time_string() << ' ' << direction << ' ' << score << "\n";
    this->out.flush();
}

Log::Log(const string& file_path, string prefix) {
    out.open(file_path);
    this->prefix = std::move(prefix);
}
