#pragma once
#include "Pawn.h"

class Rook : virtual public Piece
{
private:
	bool hasMoved;


public:

	Rook(int ri, int ci, COLOR c, chess_Board* b);


	virtual void draw() override;
	virtual bool isLegalMove(Position D) override;
	bool getHasMoved() const;
	void setHasMoved(bool);
};