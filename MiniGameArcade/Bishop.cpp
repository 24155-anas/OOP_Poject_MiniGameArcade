#include "Bishop.h"
Bishop::Bishop(int ri, int ci, COLOR c, chess_Board* b) : Piece(ri, ci, c, b) {}

void Bishop::draw() {

	//yaha pe color check hoga
	if (clr == BLACK_P) {
		cout << "b";
	}
	else {
		cout << "B";
	}
}

bool Bishop::isLegalMove(Position D) {

	return (isDiagonal(this->P, D) && isDiagonalPathClear(this->board, this->P, D));
}
