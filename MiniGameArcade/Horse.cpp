#include "Horse.h"
Horse::Horse(int ri, int ci, COLOR c, chess_Board* b) : Piece(ri, ci, c, b) {}

void Horse::draw() {

	//yaha pe color check hoga
	if (clr == BLACK_P) {
		cout << "h";
	}
	else {
		cout << "H";
	}
}

bool Horse::isLegalMove(Position D) {

	int delta_row = abs(D.row_i - this->P.row_i);
	int delta_col = abs(D.col_i - this->P.col_i);

	if (delta_row == 2 && delta_col == 1) {
		return true;
	}
	else if (delta_col == 2 && delta_row == 1) {
		return true;
	}

	return false;
}
