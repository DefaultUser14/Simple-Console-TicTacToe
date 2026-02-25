#include "field.h"
#include <iostream>

Field::Field() {
    for (int i = 0; i < 9; i++) {
        board[i] = "_";
    }
    column_names = {" ","A", "B", "C"};
    row_names = {"1", "2", "3"};
}

void Field::print() const{
    for (int i = 0; i < 4; i++){
        std::cout << column_names[i];
    }
    std::cout << "\n";

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 4; column++) {
            if (column == 0) {
                std::cout << row_names[row];
            } else {
                std::cout << board[row * 3 + (column - 1)];
            }
        }
        std::cout << "\n";
    }
}

void Field::place(char column_str, char row_str, const std::string& type) {
    int column = column_str - 'A';
    int row = row_str - '1';

    board[row *3 + column] = type;
}

void Field::place_ai(int index, const std::string& type) {
    board[index] = type;
}

bool Field::is_free(char column_str, char row_str) const {
    int column = column_str - 'A';
    int row = row_str - '1';

    return board[row * 3 + column] == "_";
}

bool Field::check_draw() const {
    for (const auto& cell : board) {
        if (cell == "_") {
            return false;
        }
    }
    return true;
}


bool Field::check_win(const std::string& type) const {
    bool win = false;

    for (int column = 0; column < 3; column++) {
        int counter = 0;
        for (int row = 0; row < 3; row++) {
            if (board[row * 3 + column] == type) {
                counter++;
            }
        }
        if (counter == 3) {
            win = true;
            break;
        } 
    }

    if (!win) {
        for (int row = 0; row < 3; row++) {
            int counter = 0;
            for (int column = 0; column < 3; column++) {
                if (board[row * 3 + column] == type) {
                    counter++;
                }
            }
            if (counter == 3) {
                win = true;
                break;
            }
        }
    }

    if (!win) {
        int counter = 0;
        for (int diagonal = 0; diagonal < 9; diagonal += 4) {
            if (board[diagonal] == type) {
                counter++;
            }
            if (counter == 3) {
                win = true;
            }
        }
    }

    if (!win) {
        int counter = 0;
        for (int diagonal = 2; diagonal < 7; diagonal += 2) {
            if (board[diagonal] == type) {
                counter++;
            }
            if (counter == 3) {
                win = true;
            }
        }
    }
    return win;
}

const std::array<std::string, 9>& Field::get_board() const {
    return board;
}