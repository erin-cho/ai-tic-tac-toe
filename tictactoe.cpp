//
// Created by Erin Cho on 5/28/20.
//

#include "tictactoe.h"
#include <iostream>

//private methods

//fillBoard
//post: board consists of spaces
void tictactoe::fillBoard()
{
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = " ";
        }
    }
}

//acceptDiff
//accepts the level of difficulty from player's input
void tictactoe::acceptDiff()
{
    std::string diff;
    std::cin >> diff;
    if (diff == "h" || diff == "H") {
        levelHard = true;
    } else {
        levelHard = false;
    }
}

//acceptValue
//post: accepts a value from player
size_t tictactoe::acceptValue()
{
    size_t value;
    std::cin >> value;
    //player must input a value within the range of the board
    while (!(value >= 1 && value <= BOARD_SIZE * BOARD_SIZE)) {
        std::cout << "You did not input a valid number. Try again." << std::endl;
        std::cin >> value;
    }
    return value;
}

//isEmpty
//pre: row and col are valid
//post: returns true if spot is empty
bool tictactoe::isEmpty(size_t row, size_t col)
{
    return board[row][col] == " ";
}

//setPlayer
//pre: row and col are valid
//post: sets spot to player's piece
//makes it easier to set the player's piece
void tictactoe::setPlayer(size_t row, size_t col)
{
    board[row][col] = PLAYER_PIECE;
}

//setCPU
//pre: row and col are valid
//post: sets spot to CPU's piece
//makes it easier to set the CPU's piece
void tictactoe::setCPU(size_t row, size_t col)
{
    board[row][col] = CPU_PIECE;
}

//playerGo
//player's turn, places player's piece in specified spot
void tictactoe::playerGo()
{
    size_t value = acceptValue();
    size_t count = 0;
    //find out which column value is in
    while (value > BOARD_SIZE) {
        value = value - BOARD_SIZE;
        ++count;
    }

    if (value == 1) {
        if (isEmpty(count, 0)) {
            setPlayer(count, 0);
        } else {
            std::cout << "You did not input a valid number. Try again." << std::endl;
            playerGo();
        }
    }
    else if (value == 2) {
        if (isEmpty(count, 1)) {
            setPlayer(count, 1);
        } else {
            std::cout << "You did not input a valid number. Try again." << std::endl;
            playerGo();
        }
    }
    else if (value == 3) {
        if (isEmpty(count, 2)) {
            setPlayer(count, 2);
        } else {
            std::cout << "You did not input a valid number. Try again." << std::endl;
            playerGo();
        }
    }

    displayBoard();

}

//CPUGo
//computer's turn, places piece in this order:
// where there's a win (two CPU pieces in a line),
// where there's a loss (two player's pieces in a line), or
// from first spot to last spot
void tictactoe::CPUGo()
{
    if (!gameOver()) {
        bool turnTaken = false;
        //if middle spot is empty, go in the middle first
        if (isEmpty(BOARD_SIZE / 2, BOARD_SIZE / 2)) {
            setCPU(BOARD_SIZE / 2, BOARD_SIZE / 2);
            turnTaken = true;
        }
        //only in hard level
        else if (levelHard)
        {
            //check for and make winning move
            checkTwoHor(turnTaken, CPU_PIECE);
            checkTwoVer(turnTaken, CPU_PIECE);
            checkTwoDiag1(turnTaken, CPU_PIECE);
            checkTwoDiag2(turnTaken, CPU_PIECE);

            //if can't win yet, check and block player's winning move, if any
            checkTwoHor(turnTaken, PLAYER_PIECE);
            checkTwoVer(turnTaken, PLAYER_PIECE);
            checkTwoDiag1(turnTaken, PLAYER_PIECE);
            checkTwoDiag2(turnTaken, PLAYER_PIECE);
        }

        //if still haven't gone, start from 1 and go in order until find an open spot
        size_t row = 0;
        size_t col = 0;
        while (row < BOARD_SIZE && !turnTaken) {
            while (col < BOARD_SIZE && !turnTaken) {
                if (isEmpty(row, col)) {
                    setCPU(row, col);
                    turnTaken = true;
                }
                ++col;
            }
            ++row;
            col = 0;
        }
        std::cout << "\nCPU's turn: " << std::endl;
        displayBoard();
    }
    if (!gameOver()) {
        std::cout << "\nYour turn: " << std::endl;
    }
}

//checkTwoHor
//checks if can win/lose horizontally (2 pieces in a line)
void tictactoe::checkTwoHor(bool &turnTaken, const std::string &piece)
{
    size_t count = 0;
    size_t row1 = 0;
    size_t col1 = 0;
    if (!turnTaken) {
        //check if can win (2 of CPU's pieces in a line)
        for (size_t row = 0; row < BOARD_SIZE; ++row) {
            for (size_t col = 0; col < BOARD_SIZE; ++col) {
                if (board[row][col] == piece) {
                    ++count;
                } else {
                    row1 = row;
                    col1 = col;
                }
            }
            if (count == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                setCPU(row1, col1);
                turnTaken = true;
            }
            count = 0;
        }
    }
}

//checkTwoVer
//checks if can win/lose vertically (2 pieces in a line)
void tictactoe::checkTwoVer(bool &turnTaken, const std::string &piece)
{
    size_t count = 0;
    size_t row1 = 0;
    size_t col1 = 0;
    if (!turnTaken) {
        for (size_t col = 0; col < BOARD_SIZE; ++col) {
            for (size_t row = 0; row < BOARD_SIZE; ++row) {
                if (board[row][col] == piece) {
                    ++count;
                } else {
                    col1 = col;
                    row1 = row;
                }
            }
            if (count == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                setCPU(row1, col1);
                turnTaken = true;
            }
            count = 0;
        }
    }
}

//checkTwoDiag1
//checks if can win/lose diagonally
// (2 pieces in a line, from top left to bottom right)
void tictactoe::checkTwoDiag1(bool &turnTaken, const std::string &piece)
{
    size_t count = 0;
    size_t row1 = 0;
    size_t col1 = 0;
    if (!turnTaken) {
        for (size_t i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][i] == piece) {
                ++count;
            } else {
                row1 = i;
                col1 = i;
            }
        }
        if (count == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
            setCPU(row1, row1);
            turnTaken = true;
        }
    }
}

//checkTwoDiag2
//checks if can win/lose diagonally
// (2 pieces in a line, from top right to bottom left)
void tictactoe::checkTwoDiag2(bool &turnTaken, const std::string &piece)
{
    size_t count = 0;
    size_t row1 = 0;
    size_t col1 = 0;
    if (!turnTaken) {
        for (size_t row = 0; row < BOARD_SIZE; ++row) {
            if (board[row][BOARD_SIZE - 1 - row] == piece) {
                ++count;
            } else {
                row1 = row;
                col1 = BOARD_SIZE - 1 - row;
            }
        }
        if (count == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
            setCPU(row1, col1);
            turnTaken = true;
        }
    }
}

//displayBoard
//post: displays current board
void tictactoe::displayBoard()
{
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        if (i != 0) {
            std::cout << "\n---+---+---" << "\n";
        }
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            if (j != 0) {
                std::cout << "|";
            }
            std::cout << " " << board[i][j] << " ";
        }
    }
    std::cout << std::endl;
}

//playerWins
//post: returns true if player wins
bool tictactoe::playerWins()
{
    size_t countHor = 0;
    size_t countVer = 0;
    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        for (size_t col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == PLAYER_PIECE) {
                ++countHor;
            }
            if (board[col][row] == PLAYER_PIECE) {
                ++countVer;
            }
        }
        if (countHor == BOARD_SIZE || countVer == BOARD_SIZE) {
            return true;
        }
        countHor = 0;
        countVer = 0;
    }

    size_t diag1 = 0;
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][i] == PLAYER_PIECE) {
            ++diag1;
        }
    }
    if (diag1 == BOARD_SIZE) {
        return true;
    }

    size_t diag2 = 0;
    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        if (board[row][BOARD_SIZE - 1 - row] == PLAYER_PIECE) {
            ++diag2;
        }
    }
    return diag2 == BOARD_SIZE;
}

//CPUWins
//post: returns true if CPU wins
bool tictactoe::CPUWins()
{
    size_t countHor = 0;
    size_t countVer = 0;
    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        for (size_t col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == CPU_PIECE) {
                ++countHor;
            }
            if (board[col][row] == CPU_PIECE) {
                ++countVer;
            }
        }
        if (countHor == BOARD_SIZE || countVer == BOARD_SIZE) {
            return true;
        }
        countHor = 0;
        countVer = 0;
    }

    size_t diag1 = 0;
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][i] == CPU_PIECE) {
            ++diag1;
        }
    }
    if (diag1 == BOARD_SIZE) {
        return true;
    }

    size_t diag2 = 0;
    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        if (board[row][BOARD_SIZE - 1 - row] == CPU_PIECE) {
            ++diag2;
        }
    }
    return diag2 == BOARD_SIZE;
}

//draw
//post: returns true if the game is a draw
bool tictactoe::draw()
{
    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        for (size_t col = 0; col < BOARD_SIZE; ++col) {
            //if there's an empty space, not a draw yet
            if (isEmpty(row, col)) {
                return false;
            }
        }
    }
    return true;
}

//gameOver
//post: returns true if game over (aka player wins, CPU wins, or it's a draw)
bool tictactoe::gameOver()
{
    return playerWins() || CPUWins() || draw();
}


//public methods

//constructor
tictactoe::tictactoe()
{
    fillBoard();
    acceptDiff();
}

//playGame
//public function to start game
void tictactoe::playGame()
{
    fillBoard();

    while (!gameOver()) {
        playerGo();
        CPUGo();
    }

    if (playerWins()) {
        std::cout << "\nYou win!!" << std::endl;
    } else if (CPUWins()) {
        std::cout << "\nYou lose :(" << std::endl;
    } else {
        std::cout << "\nIt's a tie!" << std::endl;
    }
}