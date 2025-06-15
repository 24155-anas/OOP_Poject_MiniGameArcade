#include "chess_Board.h"
#include "chess_Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"
#include "ChessGraphics.h"

chess_Board::chess_Board() {
	graphics = nullptr;
	//jab board bane to pieces k sath bane
	turn = WHITE_P;


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pieces[i][j] = nullptr;
		}


	}


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 1 || i == 6) {
				if (i == 1) {
					pieces[i][j] = new Pawn(i, j, BLACK_P, this);
				}
				else {
					pieces[i][j] = new Pawn(i, j, WHITE_P, this);
				}
			}


			else {
				pieces[i][j] = nullptr;
			}
		}
	}
	// black major pieces (row 0)
	pieces[0][0] = new Rook(0, 0, BLACK_P, this);
	pieces[0][1] = new Horse(0, 1, BLACK_P, this);
	pieces[0][2] = new Bishop(0, 2, BLACK_P, this);
	pieces[0][3] = new Queen(0, 3, BLACK_P, this);
	pieces[0][4] = new King(0, 4, BLACK_P, this);
	pieces[0][5] = new Bishop(0, 5, BLACK_P, this);
	pieces[0][6] = new Horse(0, 6, BLACK_P, this);
	pieces[0][7] = new Rook(0, 7, BLACK_P, this);

	// white major pieces (row 7)
	pieces[7][0] = new Rook(7, 0, WHITE_P, this);
	pieces[7][1] = new Horse(7, 1, WHITE_P, this);
	pieces[7][2] = new Bishop(7, 2, WHITE_P, this);
	pieces[7][3] = new Queen(7, 3, WHITE_P, this);
	pieces[7][4] = new King(7, 4, WHITE_P, this);
	pieces[7][5] = new Bishop(7, 5, WHITE_P, this);
	pieces[7][6] = new Horse(7, 6, WHITE_P, this);
	pieces[7][7] = new Rook(7, 7, WHITE_P, this);
}



void chess_Board::play() {

	//display_board();
	Position source, destination;
	while (true) {
		display_board();
		if (turn == WHITE_P) {
			cout << "whites turn\n";
		}
		else {
			cout << "Blacks turn\n";
		}
		//pehle postion k coordinats lelo
		do {
			do {
				do {
					cout << "Select Source: ";
					cin >> source.row_i >> source.col_i;

				} while (isValidSource(source) == false);
				cout << "Select destination: ";
				cin >> destination.row_i >> destination.col_i;

			} while (isValidDestination(destination) == false);
																										//board pe legality checking
		} while ((pieces[source.row_i][source.col_i]->isLegalMove(destination) == false) || isMoveLegal(source, destination) == false);

		//pieces[source.row_i][source.col_i]->move(destination);
		this->updateBoard(source, destination);
		
		//check pawn promotion here
		if (isPromotionPossible(this->turn)) {
			//////////////////
			PromotePawn(this->turn);
		}
		this->change_turn(turn);

		if (isCheck(turn)) {
			if (turn == WHITE_P) {
				cout << " WHITE CHECK " << endl;

			}
			else {
				cout << "BLACK CHECK\n";
			}
		}
		if (isCheckMate(turn)) {
			if (turn == WHITE_P) {
				cout << "WHITE CHECKMated:: Black Wins " << endl;

			}
			else {
				cout << "BLACK CHECKMated :: white wins\n";
			}

			//break the loop 
			break;
		}
		if (isStaleMate(turn)) {
			cout << "Game is Draw!\n";
			break;
		}
	}

}
void chess_Board::display_board() {
	cout << "\n   ";
	for (int col = 0; col < 8; col++) {
		cout << col << " ";
	}
	cout << "\n";

	for (int i = 0; i < 8; i++) {
		cout << i << "  ";
		for (int j = 0; j < 8; j++) {
			if (pieces[i][j] == nullptr) {
				cout << "- ";
			}
			else {
				pieces[i][j]->draw();
				cout << " ";
			}
		}
		cout << i << "\n";
	}

	cout << "   ";
	for (int col = 0; col < 8; col++) {
		cout << col << " ";
	}
	cout << "\n\n";
}



bool chess_Board::isValidSource(Position s) {
	if ((pieces[s.row_i][s.col_i] == nullptr) || (pieces[s.row_i][s.col_i]->getCOLOR() != turn)) {
		return false;
	}

	return true;
}

bool chess_Board::isValidDestination(Position d) {
	//agr piece us jaga ha tab hi getcolor call kro wrna eroor ayega
	//agr pehle condition and ki falso hojaye to short cicuit hojayega
	if (pieces[d.row_i][d.col_i] != nullptr && pieces[d.row_i][d.col_i]->getCOLOR() == turn) {
		return false;
	}

	//king capture ni hoskta
	
	if (dynamic_cast<King*>(getPiece(d))) {
		//yani agr to destination pe king ha to waha ni jaya jaskta irrespective of color so return false
		return false;
	}
	return true;
}

void chess_Board::change_turn(COLOR& turn) {
	if (turn == BLACK_P) {
		turn = WHITE_P;
	}
	else {
		turn = BLACK_P;
	}
}

Piece* chess_Board::getPiece(Position p) {
	return pieces[p.row_i][p.col_i];
}

void chess_Board::updateBoard(Position s, Position d) {

	if (s.row_i < 0 || s.row_i >= 8 || s.col_i < 0 || s.col_i >= 8 || d.row_i < 0 || d.row_i >= 8 || d.col_i < 0 || d.col_i >= 8) {
		return;
	}

	Piece* movingPiece = pieces[s.row_i][s.col_i];
	if (!movingPiece) {
		return;
	}
	//castling move
	King* king = dynamic_cast<King*>(movingPiece);
	if (king && abs(d.col_i - s.col_i) == 2 && s.row_i == d.row_i) {
		bool kingside = (d.col_i > s.col_i);
		int row = s.row_i;

		//deciding k konse coords honge rook k asper the type of castling
		int rookColFrom = kingside ? 7 : 0;
		int rookColTo = kingside ? 5 : 3;

		Rook* rook = dynamic_cast<Rook*>(pieces[row][rookColFrom]);
		if (rook) {
			//move king
			pieces[d.row_i][d.col_i] = king;
			pieces[s.row_i][s.col_i] = nullptr;
			king->setPosition(d);
			king->setHasMoved(true);

			//move rook
			pieces[row][rookColTo] = rook;
			pieces[row][rookColFrom] = nullptr;
			rook->setPosition({ row, rookColTo });
			rook->setHasMoved(true);
		}
		return;
	}


	//normal move
	if (pieces[d.row_i][d.col_i] != nullptr) {
		delete pieces[d.row_i][d.col_i];
	}

	pieces[d.row_i][d.col_i] = movingPiece;
	pieces[s.row_i][s.col_i] = nullptr;
	movingPiece->setPosition(d);

	//agr to king ya rook hi selected piece they to unka sethasmoved=true
	if (king) {
		king->setHasMoved(true);
	}
	else {
		Rook* rook = dynamic_cast<Rook*>(movingPiece);
		if (rook) {
			rook->setHasMoved(true);
		}
	}
}



Position chess_Board::findKing(COLOR turn) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			//board k hr ingez ko dynamic cast kr k check kro
			Piece* p = this->pieces[i][j];
			King* k = dynamic_cast<King*>(p);
			if (k != nullptr && k->getCOLOR() == turn) {
				return Position{ i,j };
			}
		}
	}
	return Position{ -1, -1 };
}

bool chess_Board::isCheck(COLOR king_color) {

	Position king_p = findKing(king_color);
	COLOR opponent = (king_color == WHITE_P) ? BLACK_P : WHITE_P;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* p = pieces[i][j];
			if (p != nullptr && p->getCOLOR() == opponent) {
				if (p->isLegalMove(king_p)) {
					return true;
				}
			}


		}
	}
	return false;
}


bool chess_Board::hasAnyLegalMove(COLOR turn) {
	//COLOR opponent;
	//if (turn == BLACK_P) {
	//	opponent = WHITE_P;
	//}
	//else {
	//	opponent = BLACK_P;
	//}
	for (int r1 = 0; r1 < 8; r1++) {
		for (int c1 = 0; c1 < 8; c1++) {
			Piece* piece = pieces[r1][c1];

			if (piece && piece->getCOLOR() == turn) {
				Position from = { r1, c1 };

				for (int r2 = 0; r2 < 8; r2++) {
					for (int c2 = 0; c2 < 8; c2++) {
						Position to = { r2, c2 };

						if (r1 == r2 && c1 == c2) continue;

						///////////////////
						if (piece->isLegalMove(to)) {

							Piece* captured = pieces[r2][c2];
							pieces[r2][c2] = pieces[r1][c1];
							pieces[r1][c1] = nullptr;

							Position originalPos = piece->getPosition();
							piece->setPosition(to);


							bool isStillInCheck = isCheck(turn);

							//udoing the move
							piece->setPosition(originalPos);
							pieces[r1][c1] = piece;
							pieces[r2][c2] = captured;

							if (isStillInCheck == false) {
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}



bool chess_Board::isCheckMate(COLOR turn) {

	//isCheck doisre ka king dekhraha k wo check me ha k ni
	//has anyLegal wala usi turn k pieces ko check krr aha for any valid move so its a contradiction
	if (isCheck(turn) && !hasAnyLegalMove(turn)) {
		return true;
	}
	return false;
}

bool chess_Board::isPromotionPossible(COLOR turn) {

	int row = (turn == WHITE_P) ? 0 : 7;

	for (int i = 0; i < 8; i++) {
		Piece* p = pieces[row][i];

		if (p != nullptr && dynamic_cast<Pawn*>(p) && p->getCOLOR() == turn) {
			return true;
		}

	}
	return false;
}
void chess_Board::PromotePawn(COLOR turn) {
	int row = (turn == WHITE_P) ? 0 : 7;
	//agr to promotion possible ha to aik menu show kro user ko aur user ki choice se us pawn ko replace krdo us piece se 
	if (isPromotionPossible(turn)) {

		for (int i = 0; i < 8; i++) {
			Piece* p = pieces[row][i];


			//choices
			if (p != nullptr && dynamic_cast<Pawn*>(p) && p->getCOLOR() == turn) {
				cout << "Promoting  pawn: \n";
				cout << "Promoting a pawn at: " << row << ", " << i << ") to:\n";
				cout << "1. Queen\n";
				cout << "2. Rook\n";
				cout << "3. Bishop\n";
				cout << "4. Knight\n";
				cout << "Enter choice: ";

				int choice;
				cin >> choice;


				delete pieces[row][i];
				pieces[row][i] = nullptr;
				switch (choice) {
				case 1:
					pieces[row][i] = new Queen(row, i, turn, this);
					break;
				case 2:
					pieces[row][i] = new Rook(row, i, turn, this);
					break;
				case 3:
					pieces[row][i] = new Bishop(row, i, turn, this);
					break;
				case 4:
					pieces[row][i] = new Horse(row, i, turn, this);
					break;
				default:
					cout << "Invalid choice. Defaulting to Queen.\n";
					pieces[row][i] = new Queen(row, i, p->getCOLOR(), this);
					break;
				}
			}
		}
	}
}




bool chess_Board::isStaleMate(COLOR turn) {
	return !isCheck(turn) && !hasAnyLegalMove(turn);
}


bool chess_Board::squareUnderAttack(Position pos, COLOR defenderColor) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* p = pieces[i][j];
			if (p && p->getCOLOR() != defenderColor) {
				if (p->isLegalMove(pos))
					return true;
			}
		}
	}
	return false;
}

// do types ki castling hoti ha
// queen side and kingside 

bool chess_Board::canCastle(COLOR turn, bool kingside) {
	//agr white then king ki row 7 hogi and viceversa
	int row = (turn == WHITE_P) ? 7 : 0;

	int kingCol = 4;
	//if castling is kingside, rook is on the 7th col and viceversa
	int rookCol = kingside ? 7 : 0;

	King* king = dynamic_cast<King*>(pieces[row][kingCol]);
	Rook* rook = dynamic_cast<Rook*>(pieces[row][rookCol]);

	if (!king || !rook) {
		return false;
	}
	if (king->getHasMoved() || rook->getHasMoved()) {
		return false;
	}

	if (kingside) {
		//for kingside 
		for (int col = 5; col <= 6; col++) {
			if (pieces[row][col] != nullptr)
				return false;
		}
		//ab check kro k jis squares pe king ho k jayega wo under attack ni hona chiye
		for (int i = 0; i <= 2; i++) {
			Position pos = { row,kingCol + i };
			if (squareUnderAttack(pos, turn))
				return false;
		}
	}
	else {
		//for queen side
		for (int col = 1; col <= 3; col++) {
			if (pieces[row][col] != nullptr)
				return false;
		}

		//ab check kro k jis squares pe king ho k jayega wo under attack ni hona chiye

		for (int i = 0; i <= 2; i++) {
			Position pos = { row,kingCol - i };
			if (squareUnderAttack(pos, turn))
				return false;
		}
	}

	//king ko check me bhi ni hona chahiye
	if (isCheck(turn))
		return false;

	return true;
}


COLOR chess_Board::getTurn() {
	return this->turn;
}




















void chess_Board::setGraphics(ChessGraphics* gfx) {
	graphics = gfx;
}

ChessGraphics* chess_Board::getGraphics() {
	return graphics;
}

void chess_Board::playWithGraphics() {
	if (!graphics) {
		cout << "Graphics not initialized! Using console mode.\n";
		play();
		return;
	}

	if (!graphics->initGraphics()) {
		cout << "Failed to initialize graphics! Using console mode.\n";
		play();
		return;
	}

	Position source, destination;
	bool moveComplete = false;

	while (!graphics->shouldClose()) {

		if (graphics->handleInput(source, destination)) {
			moveComplete = true;
		}

		if (moveComplete) {

			if (!isCheckMate(WHITE_P) && !isCheckMate(BLACK_P)) {
				if (isValidSource(source)) {
					if (isValidDestination(destination)) {
						if (pieces[source.row_i][source.col_i]->isLegalMove(destination)) {
							if (isMoveLegal(source, destination)) {
								pieces[source.row_i][source.col_i]->move(destination);
								updateBoard(source, destination);
								change_turn(turn);
							}
							else {
								graphics->showCenteredMessage("Your King remains in CHECK, Illegal move!", RED);
							}
						}
						else {
							graphics->showCenteredMessage("Illegal move!", RED);
						}
					}
					else {
						graphics->showCenteredMessage("Invalid destination!", RED);
					}
				}
				else {
					graphics->showCenteredMessage("Invalid source! Select your own piece.", RED);
				}
			}

			moveComplete = false;
			graphics->clearHighlight();
		}

		//yaha pedraw game status ka func add hoa render me 
		graphics->render();
	}

	graphics->closeGraphics();
}



void chess_Board::deleteAllPieces() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (pieces[i][j] != nullptr) {
				delete pieces[i][j];
				pieces[i][j] = nullptr;
			}
		}
	}
}

chess_Board::~chess_Board() {
	deleteAllPieces();
}



Piece* chess_Board::simulateMove(Position src, Position dest) {
	Piece* captured = pieces[dest.row_i][dest.col_i];
	pieces[dest.row_i][dest.col_i] = pieces[src.row_i][src.col_i];
	pieces[src.row_i][src.col_i] = nullptr;
	return captured;
}

void chess_Board::undoMove(Position src, Position dest, Piece* captured) {
	pieces[src.row_i][src.col_i] = pieces[dest.row_i][dest.col_i];
	pieces[dest.row_i][dest.col_i] = captured;
}


//this ones for checking legality on board 
//yani aik move k baad usi color ka king check me nai rah skta 
bool chess_Board::isMoveLegal(Position s, Position d) {

	Piece* piece = getPiece(s);

	Piece* captured = simulateMove(s, d);

	bool stillInCheck = isCheck(piece->getCOLOR());
	undoMove(s, d, captured);

	if (stillInCheck == true) {
		return false;
	}
	else {
		return true;
	}
	
}


//ye wala func saare legal moves of a selection return krega
Dynamic_array<Position> chess_Board::getLegalMoves(Position pos) {
	Dynamic_array<Position> legalMoves;
	legalMoves.clear();
	if (!isValidSource(pos)) {
		return legalMoves;
	}
	Piece* piece = getPiece(pos);
	if (!piece) return legalMoves;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Position dest{ i, j };

			if (pos.row_i == i && pos.col_i == j) continue;


			if (isValidDestination(dest) && piece->isLegalMove(dest)) {
				
				Piece* captured = simulateMove(pos, dest);
				bool leavesKingInCheck = isCheck(piece->getCOLOR());
				undoMove(pos, dest, captured);

				if (!leavesKingInCheck) {
					legalMoves.push(dest);
				}
			}
		}
	}

	return legalMoves;
}

//this one returns positions of the ccould be caputred pieces
Dynamic_array<Position> chess_Board::getCaptureMoves(Position pos) {
	Dynamic_array<Position> captureMoves;
	captureMoves.clear();
	if (!isValidSource(pos)) {
		return captureMoves;
	}

	Piece* piece = getPiece(pos);
	if (!piece) return captureMoves;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Position dest{ i, j };

			if (pos.row_i == i && pos.col_i == j) continue;
			Piece* target = getPiece(dest);
			if (!target) continue;

			if (target->getCOLOR() != piece->getCOLOR() && piece->isLegalMove(dest) && isValidDestination(dest))
			{
				Piece* captured = simulateMove(pos, dest);
				bool leavesKingInCheck = isCheck(piece->getCOLOR());
				undoMove(pos, dest, captured);

				if (!leavesKingInCheck) {
					captureMoves.push(dest);
				}
			}
		}
	}
	return captureMoves;
}