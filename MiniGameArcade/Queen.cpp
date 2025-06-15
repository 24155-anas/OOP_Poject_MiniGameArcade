#include "Queen.h"

Queen::Queen(int ri, int ci, COLOR c, chess_Board* b) : Piece(ri, ci, c, b), Rook(ri, ci, c, b), Bishop(ri, ci, c, b) {}

void Queen::draw() {

	//yaha pe color check hoga

	if (clr == BLACK_P) {
		cout << "q";
	}
	else {
		cout << "Q";
	}
}

bool Queen::isLegalMove(Position D) {
	//yaha pe bishop aur rook ki legality check hogi 
	return Rook::isLegalMove(D) || Bishop::isLegalMove(D);
}
