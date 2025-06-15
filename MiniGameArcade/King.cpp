#include "King.h"
#include "chess_Board.h"
King::King(int ri, int ci, COLOR c, chess_Board* b) : Piece(ri, ci, c, b), hasMoved(false) {}

void King::draw() {

    //yaha pe color check hoga

    if (clr == BLACK_P) {
        cout << "k";
    }
    else {
        cout << "K";
    }
}

bool King::isLegalMove(Position D) {
    if (D.row_i < 0 || D.row_i >= 8 || D.col_i < 0 || D.col_i >= 8) {
        return false;
    }


    if (!hasMoved && P.row_i == D.row_i) {
        //king side castling
        if (D.col_i == 6) {
            return board->canCastle(clr, true);
        }
        //queenside castling
        if (D.col_i == 2) {
            return board->canCastle(clr, false);
        }
    }


    int dr = abs(D.row_i - this->P.row_i);
    int dc = abs(D.col_i - this->P.col_i);

    if (dr > 1 || dc > 1) {
        return false;
    }

    //destination khali ho ya opponent
    Piece* destinationPiece = board->getPiece(D);
    if (destinationPiece != nullptr && destinationPiece->getCOLOR() == this->clr) {
        return false;
    }




    return true;

}


bool King::getHasMoved()const {
    return this->hasMoved;
}
void King::setHasMoved(bool moved) {
    this->hasMoved = moved;
}