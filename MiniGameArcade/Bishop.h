#pragma once
#include "chess_Piece.h"
class Bishop :virtual public Piece
{
private:



public:

	Bishop(int ri, int ci, COLOR c, chess_Board* b);


	virtual void draw() override;
	virtual bool isLegalMove(Position D) override;

};

