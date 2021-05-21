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
    // cheat的内容
    string content;
public:
    CheatModule();

    // 是否允许新的cheat
    bool canCheat();

    // 设置cheat
    void setCheat(string content);

    // 是否需要检测cheat生效
    bool needDetect();

    // cheat生效
    void doCheat();
};


#endif //LAB6_CHEATMODULE_H
