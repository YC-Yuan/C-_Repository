//
// Created by WaiWaiXi on 2021/5/21.
//

#include "CheatModule.h"

#include <utility>

CheatModule::CheatModule() = default;

bool CheatModule::can_cheat() const {
    return !active && !done;
}

void CheatModule::set_cheat(string cheat_content, int cheat_turn) {
    active = true;
    this->turn = cheat_turn;
    this->content = std::move(cheat_content);
}

bool CheatModule::need_detect(int detect_turn) const {
    if (detect_turn == turn) { return false; }
    return active && !done;
}

void CheatModule::do_cheat() {
    this->done = true;
}





