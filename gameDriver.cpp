#include <iostream>

#include "tictactoe.h"

int main()
{

    std::cout << "Welcome to Tic-Tac-Toe!\n" << std::endl;
    std::cout << " 1 | 2 | 3 " << "\n" << "---+---+---" << "\n"
              << " 4 | 5 | 6 " << "\n" << "---+---+---" << "\n"
              << " 7 | 8 | 9 " << std::endl;

    std::cout << "\nChoose the level of difficulty: easy or hard. (E/H)" << std::endl;

    tictactoe game;

    std::cout << "\nChoose a number to start the game." << std::endl;

    game.playGame();

    return 0;
}
