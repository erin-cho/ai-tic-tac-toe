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

//takenByPlayer
//pre: row and col are valid
//post: returns true if spot is taken by player's piece
//makes it easier to set the player's piece
bool tictactoe::takenByPlayer(size_t row, size_t col)
{
    return board[row][col] == PLAYER_PIECE;
}

//takenByCPU
//pre: row and col are valid
//post: returns true if spot is taken by CPU's piece
//makes it easier to set the CPU's piece
bool tictactoe::takenByCPU(size_t row, size_t col)
{
    return board[row][col] == CPU_PIECE;
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
//post: player's turn
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
//post: computer's turn
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
        else if (levelHard){
            size_t row1 = 0;
            size_t col1 = 0;
            size_t countHor = 0;
            size_t countVer = 0;
            size_t countDiag1 = 0;
            size_t countDiag2 = 0;
            if (!turnTaken) {
                //check if can win (2 of CPU's pieces in a line)
                for (size_t row = 0; row < BOARD_SIZE; ++row) {
                    for (size_t col = 0; col < BOARD_SIZE; ++col) {
                        if (takenByCPU(row, col)) {
                            ++countHor;
                        } else {
                            row1 = row;
                            col1 = col;
                        }
                    }
                    if (countHor == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                        setCPU(row1, col1);
                        turnTaken = true;
                    }
                    countHor = 0;
                }
            }
            if (!turnTaken) {
                for (size_t col = 0; col < BOARD_SIZE; ++col) {
                    for (size_t row = 0; row < BOARD_SIZE; ++row) {
                        if (takenByCPU(row, col)) {
                            ++countVer;
                        } else {
                            col1 = col;
                            row1 = row;
                        }
                    }
                    if (countVer == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                        setCPU(row1, col1);
                        turnTaken = true;
                    }
                    countVer = 0;
                }
            }
            if (!turnTaken) {
                for (size_t i = 0; i < BOARD_SIZE; ++i) {
                    if (takenByCPU(i, i)) {
                        ++countDiag1;
                    } else {
                        row1 = i;
                        col1 = i;
                    }
                }
                if (countDiag1 == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                    setCPU(row1, row1);
                    turnTaken = true;
                }
            }
            if (!turnTaken) {
                for (size_t row = 0; row < BOARD_SIZE; ++row) {
                    if (takenByCPU(row, BOARD_SIZE - 1 - row)) {
                        ++countDiag2;
                    } else {
                        row1 = row;
                        col1 = BOARD_SIZE - 1 - row;
                    }
                }
                if (countDiag2 == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                    setCPU(row1, col1);
                    turnTaken = true;
                }
            }
            //if can't win yet, check if there are 2 of player's pieces in a line
            // (block if player can win next turn)
            if (!turnTaken) {
                countHor = 0;
                for (size_t row = 0; row < BOARD_SIZE; ++row) {
                    for (size_t col = 0; col < BOARD_SIZE; ++col) {
                        if (takenByPlayer(row, col)) {
                            ++countHor;
                        } else {
                            row1 = row;
                            col1 = col;
                        }
                    }
                    if (countHor == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                        setCPU(row1, col1);
                        turnTaken = true;
                    }
                    countHor = 0;
                }
            }
            if (!turnTaken) {
                countVer = 0;
                for (size_t col = 0; col < BOARD_SIZE; ++col) {
                    for (size_t row = 0; row < BOARD_SIZE; ++row) {
                        if (takenByPlayer(row, col)) {
                            ++countVer;
                        } else {
                            col1 = col;
                            row1 = row;
                        }
                    }
                    if (countVer == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                        setCPU(row1, col1);
                        turnTaken = true;
                    }
                    countVer = 0;
                }
            }
            if (!turnTaken) {
                countDiag1 = 0;
                for (size_t i = 0; i < BOARD_SIZE; ++i) {
                    if (takenByPlayer(i, i)) {
                        ++countDiag1;
                    } else {
                        row1 = i;
                        col1 = i;
                    }
                }
                if (countDiag1 == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                    setCPU(row1, row1);
                    turnTaken = true;
                }
            }
            if (!turnTaken) {
                countDiag2 = 0;
                for (size_t row = 0; row < BOARD_SIZE; ++row) {
                    if (takenByPlayer(row, BOARD_SIZE - 1 - row)) {
                        ++countDiag2;
                    } else {
                        row1 = row;
                        col1 = BOARD_SIZE - 1 - row;
                    }
                }
                if (countDiag2 == BOARD_SIZE - 1 && isEmpty(row1, col1)) {
                    setCPU(row1, col1);
                    turnTaken = true;
                }
            }
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
            if (takenByPlayer(row, col)) {
                ++countHor;
            }
            if (takenByPlayer(col, row)) {
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
        if (takenByPlayer(i, i)) {
            ++diag1;
        }
    }
    if (diag1 == BOARD_SIZE) {
        return true;
    }

    size_t diag2 = 0;
    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        if (takenByPlayer(row, BOARD_SIZE - 1 - row)) {
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
            if (takenByCPU(row, col)) {
                ++countHor;
            }
            if (takenByCPU(col, row)) {
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
        if (takenByCPU(i, i)) {
            ++diag1;
        }
    }
    if (diag1 == BOARD_SIZE) {
        return true;
    }

    size_t diag2 = 0;
    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        if (takenByCPU(row, BOARD_SIZE - 1 - row)) {
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
}

//acceptDiff
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