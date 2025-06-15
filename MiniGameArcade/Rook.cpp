#include "Rook.h"
Rook::Rook(int ri, int ci, COLOR c, chess_Board* b) : Piece(ri, ci, c, b), hasMoved(false) {}

void Rook::draw() {

	//yaha pe color check hoga
	if (clr == BLACK_P) {
		cout << "r";
	}
	else {
		cout << "R";
	}
}

bool Rook::isLegalMove(Position D) {

	return (isVertical(this->P, D) && isVericalPathClear(this->board, this->P, D)) || (isHorizontal(this->P, D) && isHorizontalPathClear(this->board, this->P, D));
}

bool Rook::getHasMoved()const {
	return hasMoved;
}
void Rook::setHasMoved(bool moved) {
	this->hasMoved = moved;
}