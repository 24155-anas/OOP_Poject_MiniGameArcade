#include "ttt_Board.h"

ttt_Board::ttt_Board() {
    reset(); 
}

void ttt_Board::reset() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->cells[i][j] = '-';
        }
    }
}

void ttt_Board::display() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << this->cells[i][j] << " ";
        cout << endl;
    }
}

void ttt_Board::placeMove(int x, int y, char symbol) {

    if (x < 0 || x >= 3 || y < 0 || y >= 3 || cells[x][y] != '-') {
        throw ttt_InvalidMoveException("Invalid move:: Out of Bounds/ Cell occupied!");
    }
    cells[x][y] = symbol;
}

bool ttt_Board::checkWinner(char symbol) const {

    for (int i = 0; i < 3; i++) {
        if ((cells[i][0] == symbol && cells[i][1] == symbol && cells[i][2] == symbol) || (cells[0][i] == symbol && cells[1][i] == symbol && cells[2][i] == symbol)){
            return true;
        }
    }

    //diagonal checking
    if ((cells[0][0] == symbol && cells[1][1] == symbol && cells[2][2] == symbol) || (cells[0][2] == symbol && cells[1][1] == symbol && cells[2][0] == symbol)) {
        return true;
    }
    
    //agr koi bhi ni then return false

    return false;
}

bool ttt_Board::isDraw() const {
    //game tabhi end hogi tab saare cells fill ho chuke honge 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (cells[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}

char ttt_Board::getCell(int x, int y) const {
    return cells[x][y];
}
bool ttt_Board::isEmpty(int x, int y) const {
    return cells[x][y] == '-';
}