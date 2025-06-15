#pragma once
#include <iostream>
#include <string>
#include "Dynamic_array.h"
#include "ttt_Board.h"
#include "ttt_Player.h"
#include "ttt_HumanPlayer.h"
#include "ttt_GM.h"
#include "raylib.h"

//reversi
#include "reversi_Player.h"
#include "reversi_HumanPlayer.h"
#include "reversi_Board.h"

//chess
#include "chess_Piece.h"
#include "chess_Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Queen.h"
#include "Horse.h"
#include "King.h"
#include "Bishop.h"
#include "ChessGraphics.h"

using namespace std;

class MiniGameArcade
{
private:

    void displayMenu() const;
    int getUserChoice() const;
    void playTicTacToe();
    void playReversi();
    void playChess();
    void showGameRules(int gameChoice) const;

public:
    
    MiniGameArcade();


    ~MiniGameArcade() = default;


    void runArcade();


    void displayWelcomeMessage() const;
    void displayGoodbyeMessage() const;
};