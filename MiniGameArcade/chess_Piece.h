#include "chess_header.h"
#pragma once
#include <iostream>
#include "raylib.h"
using namespace std;

class chess_Board; //yaha forward declare hi krna parega wrna masla hoga 
class Piece
{
	//color and position k liye separate header 

protected:
	Position P;
	COLOR clr;
	chess_Board* board;

	bool isVertical(Position S, Position D);
	bool isHorizontal(Position S, Position D);
	bool isDiagonal(Position S, Position D);

	static bool isVericalPathClear(chess_Board* B, Position S, Position D);
	static bool isHorizontalPathClear(chess_Board* B, Position S, Position D);
	static bool isDiagonalPathClear(chess_Board* B, Position S, Position D);
public:
	//contructors
	Piece(int ri, int ci, COLOR c, chess_Board* b);

	virtual void draw() = 0;
	virtual bool isLegalMove(Position D) = 0;
	virtual void move(Position D); //just updates peices's coords, will call update board from board class

	virtual COLOR getCOLOR();

	void setPosition(Position p);
	Position getPosition();

	virtual ~Piece() = default;

};
