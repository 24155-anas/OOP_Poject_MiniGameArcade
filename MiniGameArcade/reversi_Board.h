#pragma once
#include <iostream>
using namespace std;
#include "reversi_Player.h"
#include "ttt_InvalidMoveException.h"
#include "raylib.h"
class reversi_Board {
private:
	char cells[8][8];
	reversi_Player* players[2];
	int turn;

	void flipHorizontal(int row, int col, char symbol);
	void flipVertical(int row, int col, char symbol);
	void flipDiagonal(int row, int col, char symbol);

public:
	reversi_Board();

	~reversi_Board();
	void setPlayers(reversi_Player* p1, reversi_Player* p2);

	bool isValidMove(int x, int y, int turn);


	void makeMove();

	void displayBoard();

	bool hasValidMoves();

	void changeTurn();
	int getCurrentPlayer();

	int checkWinner();
	bool isGameOver();
	void play();

	void playWithGraphics();
};

