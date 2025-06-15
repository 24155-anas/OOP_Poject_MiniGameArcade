#include "Pawn.h"
#include "chess_Board.h"

Pawn::Pawn(int ri, int ci, COLOR c, chess_Board* b) : Piece(ri, ci, c, b) {}

void Pawn::draw() {

    //yaha pe color check hoga
    if (clr == BLACK_P) {
        cout << "p";
    }
    else {
        cout << "P";
    }
}

bool Pawn::isLegalMove(Position newPos) {
    int dr = newPos.row_i - P.row_i;
    int dc = newPos.col_i - P.col_i;

    //white k liye oper jayega pawn so -ve and viceversa for black
    int dir = (clr == WHITE_P) ? -1 : 1;

    //one move ahead
    if (dc == 0 && dr == dir && board->getPiece(newPos) == nullptr)
        return true;

    bool onStartingRank = false;
    if (clr == WHITE_P && this->P.row_i == 6) {
        onStartingRank = true;
    }
    else if (clr == BLACK_P && this->P.row_i == 1) {
        onStartingRank = true;
    }

    //fouble step only when onStarting rank is true
    if (dc == 0 && dr == 2 * dir && onStartingRank) {

        //yaha pe dono blocks empty hone chahoye 
        Position intermediatePos = Position{ P.row_i + dir, P.col_i };
        if (board->getPiece(intermediatePos) == nullptr && board->getPiece(newPos) == nullptr)
            return true;
    }

    //diagonal capture
    if ((dc == 1 || dc == -1) && dr == dir) {
        if (board->getPiece(newPos) != nullptr && board->getPiece(newPos)->getCOLOR() != clr) {
            return true;
        }
    }

    return false;
}


Pawn::~Pawn() {
    cout << "Deleting a pawn at (" << P.row_i << ", " << P.col_i << ")\n";
}
