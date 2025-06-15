#pragma once
#include <iostream>
#include "ttt_InvalidMoveException.h"
using namespace std;

class ttt_Board {
private:

    char cells[3][3];

public:

    ttt_Board();

    void reset();

    void display() const;

    void placeMove(int x, int y, char symbol);
    bool checkWinner(char symbol) const;
    bool isDraw() const;

    char getCell(int x, int y) const;
    bool isEmpty(int x, int y) const;
};
