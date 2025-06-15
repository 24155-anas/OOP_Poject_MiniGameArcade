#pragma once
#include "ttt_Player.h"
#include <iostream>
#include "ttt_Board.h"
using namespace std;


class ttt_HumanPlayer : public ttt_Player {
public:
    ttt_HumanPlayer(char s) : ttt_Player(s) {}

    void makeMove(ttt_Board& board) override;
};