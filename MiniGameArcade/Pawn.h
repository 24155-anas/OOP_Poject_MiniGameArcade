#pragma once
#include "chess_Piece.h"

class Pawn : public Piece
{
private:



public:

	Pawn(int ri, int ci, COLOR c, chess_Board* b);


	virtual void draw() override;
	virtual bool isLegalMove(Position D) override;
	~Pawn();
};

