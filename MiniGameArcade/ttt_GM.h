#pragma once
#include "ttt_Board.h"
#include "ttt_Player.h"
#include "raylib.h"

class ttt_GM {
    ttt_Board board;
    ttt_Player* players[2];
    int turn;
public:
    ttt_GM(ttt_Player* p1, ttt_Player* p2);

    void play();
    void turn_change();

    void playWithGraphics();
};

