//
// Created by Erin Cho on 5/28/20.
//

#include <iostream>
#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

const size_t BOARD_SIZE = 3;
const std::string PLAYER_PIECE = "O";
const std::string CPU_PIECE = "X";


class tictactoe {

private:
    //tic-tac-toe board
    std::string board[BOARD_SIZE][BOARD_SIZE];

    //returns true if player chooses level hard
    bool levelHard;

    //fillBoard
    //post: board consists of spaces
    void fillBoard();

    //acceptDiff
    //accepts the level of difficulty from player's input
    void acceptDiff();

    //acceptValue
    //post: accepts a value from player
    size_t acceptValue();

    //isEmpty
    //pre: row and col are valid
    //post: returns true if spot is empty
    bool isEmpty(size_t row, size_t col);

    //setPlayer
    //pre: row and col are valid
    //post: sets spot to player's piece
    //makes it easier to set the player's piece
    void setPlayer(size_t row, size_t col);

    //setCPU
    //pre: row and col are valid
    //post: sets spot to CPU's piece
    //makes it easier to set the CPU's piece
    void setCPU(size_t row, size_t col);

    //playerGo
    //player's turn, places player's piece in specified spot
    void playerGo();

    //CPUGo
    //computer's turn, places piece in this order:
    // where there's a win (two CPU pieces in a line),
    // where there's a loss (two player's pieces in a line), or
    // from first spot to last spot
    void CPUGo();

    //checkTwoHor
    //checks if can win/lose horizontally (2 pieces in a line)
    void checkTwoHor(bool &turnTaken, const std::string &piece);

    //checkTwoVer
    //checks if can win/lose vertically (2 pieces in a line)
    void checkTwoVer(bool &turnTaken, const std::string &piece);

    //checkTwoDiag1
    //checks if can win/lose diagonally
    // (2 pieces in a line, from top left to bottom right)
    void checkTwoDiag1(bool &turnTaken, const std::string &piece);

    //checkTwoDiag2
    //checks if can win/lose diagonally
    // (2 pieces in a line, from top right to bottom left)
    void checkTwoDiag2(bool &turnTaken, const std::string &piece);

    //displayBoard
    //post: displays current board
    void displayBoard();

    //playerWins
    //post: returns true if player wins
    bool playerWins();

    //CPUWins
    //post: returns true if CPU wins
    bool CPUWins();

    //draw
    //post: returns true if the game is a draw
    bool draw();

    //gameOver
    //post: returns true if game over (aka player wins, CPU wins, or it's a draw)
    bool gameOver();


public:
    //constructor
    tictactoe();

    //playGame
    //public function to start game
    void playGame();

};


#endif //TIC_TAC_TOE_GAME_H
