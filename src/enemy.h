#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <array>

class Enemy {
    public:
    int move(const std::array<std::string, 9>& board);
    void set(const std::string&);
    const std::string& get_type() const; 

    private:
    std::string type;
};

#endif