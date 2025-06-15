#include "chess_Piece.h"
#include "chess_Board.h"

Piece::Piece(int ri, int ci, COLOR c, chess_Board* b) : P{ ri,ci }, clr(c), board(b) {}

void Piece::move(Position D) {
	this->P = D;
}

COLOR Piece::getCOLOR() {
	return clr;
}


bool Piece::isVertical(Position S, Position D) {
	return S.col_i == D.col_i;
}
bool Piece::isHorizontal(Position S, Position D) {
	return S.row_i == D.row_i;
}
bool Piece::isDiagonal(Position S, Position D) {
	int delta_r = abs(S.row_i - D.row_i);
	int delta_c = abs(S.col_i - D.col_i);
	return delta_r == delta_c;
}

bool Piece::isVericalPathClear(chess_Board* B, Position S, Position D) {
	if (S.row_i < D.row_i) {  //ooper se neeche
		for (int i = S.row_i + 1; i < D.row_i; i++) {
			if (B->getPiece(Position{ i, S.col_i }) != nullptr) {
				return false;
			}
		}
	}
	else { //neeche se ooper
		for (int i = D.row_i + 1; i < S.row_i; i++) {
			if (B->getPiece(Position{ i, S.col_i }) != nullptr) {
				return false;
			}
		}
	}
	return true;
}
bool Piece::isHorizontalPathClear(chess_Board* B, Position S, Position D) {
	if (S.col_i < D.col_i) {  //right to left
		for (int i = S.col_i + 1; i < D.col_i; i++) {
			if (B->getPiece(Position{ S.row_i, i }) != nullptr) {
				return false;
			}
		}
	}
	else { // left to right 
		for (int i = D.col_i + 1; i < S.col_i; i++) {
			if (B->getPiece(Position{ S.row_i, i }) != nullptr) {
				return false;
			}
		}
	}
	return true;
}
bool Piece::isDiagonalPathClear(chess_Board* B, Position S, Position D) {
	//total 4 cases
	int delta_r = (S.row_i - D.row_i);
	int delta_c = (S.col_i - D.col_i);

	if (delta_r < 0 && delta_c < 0) {	//top left se bottom right
		int diff = D.row_i - S.row_i - 1;
		for (int i = 1; i <= diff; i++) {
			if (B->getPiece(Position{ S.row_i + i,S.col_i + i }) != nullptr) {
				return false;
			}
		}
	}
	else if (delta_r > 0 && delta_c > 0) {	//bottom right s etop left
		int diff = S.row_i - D.row_i - 1;
		for (int i = 1; i <= diff; i++) {
			if (B->getPiece(Position{ S.row_i - i, S.col_i - i }) != nullptr) {
				return false;
			}
		}
	}
	else if (delta_r < 0 && delta_c >0) {	//top right to bottom left
		int diff = D.row_i - S.row_i - 1;
		for (int i = 1; i <= diff; i++) {
			if (B->getPiece(Position{ S.row_i + i, S.col_i - i }) != nullptr) {
				return false;
			}
		}
	}
	else if (delta_r > 0 && delta_c < 0) {	//bottom left to top right
		int diff = S.row_i - D.row_i - 1;
		for (int i = 1; i <= diff; i++) {
			if (B->getPiece(Position{ S.row_i - i, S.col_i + i }) != nullptr) {
				return false;
			}
		}
	}

	return true;
}

void Piece::setPosition(Position p) {
	this->P = p;
}
Position Piece::getPosition() {
	return this->P;
}