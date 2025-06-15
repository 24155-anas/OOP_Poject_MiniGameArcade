#pragma once
#include "chess_Piece.h"
#include "Rook.h"
#include "Bishop.h"
class Queen : public Rook, public Bishop
{
private:

public:

	Queen(int ri, int ci, COLOR c, chess_Board* b);


	virtual void draw() override;
	virtual bool isLegalMove(Position D) override;

};
