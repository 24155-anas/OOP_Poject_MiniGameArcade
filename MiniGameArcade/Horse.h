#pragma once
#include "chess_Piece.h"

class Horse :public Piece
{
private:



public:

	Horse(int ri, int ci, COLOR c, chess_Board* b);


	virtual void draw() override;
	virtual bool isLegalMove(Position D) override;

};
