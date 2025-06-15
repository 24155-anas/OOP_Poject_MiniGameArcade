#pragma once
#include "chess_Piece.h"

class King : public Piece
{
private:

	bool hasMoved;

public:

	King(int ri, int ci, COLOR c, chess_Board* b);


	virtual void draw() override;
	virtual bool isLegalMove(Position D) override;

	bool getHasMoved()const;


	void setHasMoved(bool moved);

};
