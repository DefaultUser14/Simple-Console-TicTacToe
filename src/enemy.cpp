#include "enemy.h"
#include <iostream>
#include <array>


void Enemy::set(const std::string& player_type){
    type = player_type;
}

int Enemy::move(const std::array<std::string, 9>& board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == "_") {
            return i;
        }
    }
    return -1;
}

const std::string& Enemy::get_type() const {
    return type;
}