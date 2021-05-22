//
// Created by WaiWaiXi on 2021/5/21.
//

#ifndef LAB6_CHEATMODULE_H
#define LAB6_CHEATMODULE_H

#include <string>

using namespace std;

class CheatModule {
    // 是否有人开启cheat
    bool active = false;
    // 是否已经cheat完
    bool done = false;

public:
    // cheat的内容
    string content;
    int turn;

    CheatModule();

    // 是否允许新的cheat
    bool can_cheat() const;

    // 设置cheat
    void set_cheat(string cheat_content, int cheat_turn);

    // 是否需要检测cheat生效
    bool need_detect(int detect_turn) const;

    // cheat生效后调用
    void do_cheat();
};


#endif //LAB6_CHEATMODULE_H
