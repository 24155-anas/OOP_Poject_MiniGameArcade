#pragma once
#include "chess_header.h"
#include "Dynamic_array.h"
class Piece;
class ChessGraphics;

class chess_Board
{
private:
	//pieces k pointers honge board k paas
	//jahan peice hoga waha memory assign jahan ni waha nullptr

	ChessGraphics* graphics;


	Piece* pieces[8][8];
	COLOR turn;

	void deleteAllPieces();
public:

	chess_Board();
	void play();
	void display_board();

	bool isValidSource(Position s);
	bool isValidDestination(Position d);

	void change_turn(COLOR& turn);
	Piece* getPiece(Position p);
	void updateBoard(Position s, Position d);

	bool isCheck(COLOR turn);
	bool isCheckMate(COLOR turn);
	bool hasAnyLegalMove(COLOR turn);
	Position findKing(COLOR turn);

	//additions
	bool isPromotionPossible(COLOR turn);
	void PromotePawn(COLOR turn);
	bool isStaleMate(COLOR turn);
	bool squareUnderAttack(Position pos, COLOR defenderColor);
	bool canCastle(COLOR clr, bool kingside);


	void playWithGraphics();
	void setGraphics(ChessGraphics* gfx);
	ChessGraphics* getGraphics();

	COLOR getTurn();

	~chess_Board();


	Piece* simulateMove(Position src, Position dest);
	void undoMove(Position src, Position dest, Piece* captured);
	bool isMoveLegal(Position s, Position d);

	
	Dynamic_array<Position> getLegalMoves(Position pos);
	Dynamic_array<Position> getCaptureMoves(Position pos);
};

