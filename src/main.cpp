#include <iostream>
#include <string>
#include "field.h"
#include "enemy.h"

bool validate_input(const std::string& input, const Field& field){
    if (input.length() != 2) {
        return false;
    }

    char column_str = input[0];
    char row_str = input[1];
    if (column_str > 'C' || column_str < 'A' || row_str > '3' || row_str < '1') {
        return false;
    }

    return field.is_free(column_str, row_str);
}

std::string player_turn(const std::string& player_type, const std::string& player_name, bool valid_input) {
    std::string player_input;
    if (valid_input) {
        std::cout << player_name  << "'S TURN. " << '"'<< player_type << '"' << " CHOOSE FIELD (A1-C3): ";
    } else {
        std::cout << "WRONG INPUT OR FIELD ALREADY IN USE, TRY AGAIN.\n" << player_name << " " << '"' << player_type << '"' << " CHOOSE FIELD (A1-C3): ";
    }

    std::cin >> player_input;
    std::cout << "\n";

    return player_input;
}

enum class GameMode {
    Normal,
    PC,
    Exit};

GameMode init() {
    while (true) {
        std::string player_input;
        std::cout   << "CHOOSE THE GAME MODE:\n" 
                    << "[1]NORMAL [2]PC [3]EXIT\n";

        std::cin >> player_input;

        if (player_input == "1") {
            return GameMode::Normal;
        } else if (player_input == "2") {
            return GameMode::PC;
        } else if ( player_input == "3") {
            return GameMode::Exit;
        } 

        std::cout << "WRONG INPUT, TRY AGAIN!\n";
    }
}

int main(){
    while (true) {
            
        GameMode mode = init();

        if (mode == GameMode::Exit) {
            break;
        }

        bool pc = (mode == GameMode::PC);

        Field main_field;
        Enemy enemy_pc;
        bool player_1_turn = true;
        bool valid_input = true;
        std::string player_type = "X";
        std::string player_name;
        enemy_pc.set(player_type);
        std::string player_input;

        while (true) {
            main_field.print();

            if (player_1_turn) {
                player_type = "O";
                player_name = "PLAYER 1";

                player_input = player_turn(player_type, player_name, valid_input);
                valid_input = validate_input(player_input, main_field);
                if (valid_input) {
                    char column_str = player_input[0];
                    char row_str = player_input[1];
                    main_field.place(column_str, row_str, player_type);
                    player_1_turn = !player_1_turn;
                }
            } else if (!player_1_turn && !pc) {
                player_type = "X";
                player_name = "PLAYER 2";

                player_input = player_turn(player_type, player_name, valid_input);
                valid_input = validate_input(player_input, main_field);
                if (valid_input) {
                    char column_str = player_input[0];
                    char row_str = player_input[1];
                    main_field.place(column_str, row_str, player_type);
                    player_1_turn = !player_1_turn;
                }
            } else if (!player_1_turn && pc) {
                player_name = "ENEMY";
                player_type = "X";
                main_field.place_ai(enemy_pc.move(main_field.get_board()), enemy_pc.get_type());
                player_1_turn = !player_1_turn;
            }

            if (main_field.check_win(player_type)) {
                std::cout << player_name << " WON THE ROUND!\n";
                main_field.print();
                break;
            } else if (main_field.check_draw()) {
                std::cout << "NO WINNER! DRAW!\n";
                main_field.print();
                break;
            }
        }
    }
}