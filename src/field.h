#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <array>

class Field {
    public:
    Field();
    void print() const;
    void place(char, char, const std::string&);
    void place_ai(int, const std::string&);
    bool is_free(char, char) const;
    bool check_draw() const;
    bool check_win(const std::string&) const;
    const std::array<std::string, 9>& get_board() const;

    private:
    std::array<std::string, 9> board;
    std::array<std::string, 4> column_names;
    std::array<std::string, 3> row_names;
};

#endif