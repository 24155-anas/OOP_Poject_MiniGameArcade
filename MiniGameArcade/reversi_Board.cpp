#include "reversi_Board.h"



void reversi_Board::flipHorizontal(int row, int col, char symbol) {
	//towards right
	for (int j = col + 1; j < 8; j++) {
		if (cells[row][j] == '-') break;
		if (cells[row][j] == symbol) {

			for (int k = col + 1; k < j; k++) {
				cells[row][k] = symbol;
			}
			break;
		}

	}

	//toward left
	for (int j = col - 1; j >= 0; j--) {
		if (cells[row][j] == '-') break;
		if (cells[row][j] == symbol) {
			for (int k = col - 1; k > j; k--) {
				cells[row][k] = symbol;
			}
			break;
		}

	}
}

void reversi_Board::flipVertical(int row, int col, char symbol) {
	//towards down
	for (int i = row + 1; i < 8; i++) {
		if (cells[i][col] == '-') break;
		if (cells[i][col] == symbol) {
			for (int k = row + 1; k < i; k++) {
				cells[k][col] = symbol;
			}
			break;
		}
	}

	//upwards
	for (int i = row - 1; i >= 0; i--) {
		if (cells[i][col] == '-') break;
		if (cells[i][col] == symbol) {
			for (int k = row - 1; k > i; k--) {
				cells[k][col] = symbol;
			}
			break;
		}
	}
}

void reversi_Board::flipDiagonal(int row, int col, char symbol) {
	// main doiagonal up roght
	for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) {
		if (cells[i][j] == '-') break;
		if (cells[i][j] == symbol) {

			for (int k = row + 1, l = col + 1; k < i; k++, l++) {
				cells[k][l] = symbol;
			}
			break;
		}
	}

	//up left
	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
		if (cells[i][j] == '-') break;
		if (cells[i][j] == symbol) {
			for (int k = row - 1, l = col - 1; k > i; k--, l--) {
				cells[k][l] = symbol;
			}
			break;
		}
	}

	// seconday diagonal downnleft
	for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) {
		if (cells[i][j] == '-') break;
		if (cells[i][j] == symbol) {
			for (int k = row + 1, l = col - 1; k < i; k++, l--) {
				cells[k][l] = symbol;
			}
			break;
		}
	}

	// seconday diagonal upright
	for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) {
		if (cells[i][j] == '-') break;
		if (cells[i][j] == symbol) {
			for (int k = row - 1, l = col + 1; k > i; k--, l++) {
				cells[k][l] = symbol;
			}
			break;
		}
	}
}
reversi_Board::reversi_Board() : turn(0) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cells[i][j] = '-';
		}
	}

	cells[3][3] = 'O';
	cells[3][4] = 'X';
	cells[4][3] = 'X';
	cells[4][4] = 'O';

	players[0] = nullptr;
	players[1] = nullptr;
}

reversi_Board::~reversi_Board() {
	delete players[0];
	delete players[1];
}

void reversi_Board::setPlayers(reversi_Player* p1, reversi_Player* p2) {
	players[0] = p1;
	players[1] = p2;
}

bool reversi_Board::isValidMove(int x, int y, int turn) {

	if (x < 0 || x >= 8 || y < 0 || y >= 8) {
		return false;
	}

	if (cells[x][y] != '-') {
		return false;
	}

	char playerSymbol = players[turn]->getSymbol();

	if (cells[x][y] == playerSymbol) {
		return false;
	}

	return true;
}


void reversi_Board::makeMove() {
	int x, y;
	cout << "Enter x,y: ";
	cin >> x >> y;
	if (!isValidMove(x, y, this->turn)) {
		throw ttt_InvalidMoveException("invalid move");
	}

	char playerSymbol = players[turn]->getSymbol();
	cells[x][y] = playerSymbol;
	flipDiagonal(x, y, playerSymbol);
	flipHorizontal(x, y, playerSymbol);
	flipVertical(x, y, playerSymbol);


}

void reversi_Board::displayBoard() {
	std::cout << "  0 1 2 3 4 5 6 7\n";
	for (int i = 0; i < 8; i++) {
		std::cout << i << " ";
		for (int j = 0; j < 8; j++) {
			std::cout << cells[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

bool reversi_Board::hasValidMoves() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isValidMove(i, j, this->turn)) {
				return true;
			}
		}
	}
	return false;
}

void reversi_Board::changeTurn() {
	turn = (turn + 1) % 2; 
}

int reversi_Board::getCurrentPlayer() {
	return turn;
}


bool reversi_Board::isGameOver() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->cells[i][j]=='-') {
				return false;
			}
		}
	}
	return true;
}
int reversi_Board::checkWinner() {
	int xCount = 0;
	int oCount = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->cells[i][j] == 'X') {
				xCount++;
			}
			else if (this->cells[i][j] == 'O') {
				oCount++;
			}
		}
	}

	if (xCount > oCount) {
		return 1;
	}
	else {
		return -1;
	}
}
void reversi_Board::play() {
	displayBoard();

	while (!isGameOver()) {
		cout << "Player " << (turn + 1) << " (" << players[turn]->getSymbol() << ") turn:\n";

		if (!hasValidMoves()) {
			cout << "No valid moves for player " << (turn + 1) << "\n";
			changeTurn();

			if (!hasValidMoves()) {
				cout << "Game Over!\n";

				break;
			}
			continue;
		}

		try {
			makeMove();
			displayBoard();
			changeTurn();
		}
		catch (const ttt_InvalidMoveException& e) {
			cout << "Error: " << e.what() << " Try again.\n";
		}
	}

	if (checkWinner() == 1) {
		cout << "Player X Wins\n";

	}
	else {
		cout << "Player O wins\n";
	}
}


void reversi_Board::playWithGraphics() {
	const int screenWidth = 640;
	const int screenHeight = 640;
	const int cellSize = screenWidth / 8;

	InitWindow(screenWidth, screenHeight, "Reversi");
	SetTargetFPS(60);

	Color boardColor1 = { 118, 92, 72, 255 };
	Color boardColor2 = { 148, 120, 96, 255 };
	Color bgTop = { 34, 139, 34, 255 };
	Color bgBottom = { 60, 179, 113, 255 };

	bool gameOver = false;
	string winnerText;

	while (!WindowShouldClose()) {

		if (!gameOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			int mouseX = GetMouseX();
			int mouseY = GetMouseY();
			int col = mouseX / cellSize;
			int row = mouseY / cellSize;

			if (isValidMove(row, col, turn)) {
				char symbol = players[turn]->getSymbol();
				cells[row][col] = symbol;
				flipHorizontal(row, col, symbol);
				flipVertical(row, col, symbol);
				flipDiagonal(row, col, symbol);
				changeTurn();
			}

			if (isGameOver()) {
				gameOver = true;
				int winner = checkWinner();

				if (winner == 1)
					winnerText = "Player X wins!";
				else if (winner == -1)
					winnerText = "Player O wins!";
				else
					winnerText = "It's a draw!";
			}
		}

		BeginDrawing();
		for (int y = 0; y < screenHeight; y++) {
			float t = (float)y / screenHeight;
			Color blended = {
				(unsigned char)(bgTop.r * (1 - t) + bgBottom.r * t),
				(unsigned char)(bgTop.g * (1 - t) + bgBottom.g * t),
				(unsigned char)(bgTop.b * (1 - t) + bgBottom.b * t),
				255
			};
			DrawLine(0, y, screenWidth, y, blended);
		}

		//drawing squares
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Color squareColor = ((i + j) % 2 == 0) ? boardColor1 : boardColor2;
				DrawRectangle(j * cellSize, i * cellSize, cellSize, cellSize, squareColor);
			}
		}

		//drawing pieces
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				int cx = j * cellSize + cellSize / 2;
				int cy = i * cellSize + cellSize / 2;
				int radius = cellSize / 2.5;

				if (cells[i][j] == 'X') {
					DrawCircle(cx, cy, radius, BLACK);
					DrawCircle(cx, cy, radius * 0.5, GRAY);
				}
				else if (cells[i][j] == 'O') {
					DrawCircle(cx, cy, radius, WHITE);
					DrawCircleLines(cx, cy, radius, BLACK);
					DrawCircle(cx, cy, radius * 0.5, LIGHTGRAY);
				}
			}
		}

		if (!gameOver) {
			DrawText(turn == 1 ? "Player X's Turn (Black)" : "Player O's Turn (White)", 10, screenHeight - 30, 20, DARKGREEN);
		}
		else {
			DrawRectangle(100, screenHeight / 2 - 40, 440, 80, Fade(WHITE, 0.9f));
			DrawRectangleLines(100, screenHeight / 2 - 40, 440, 80, BLACK);
			DrawText(winnerText.c_str(), 130, screenHeight / 2 - 10, 30, MAROON);
			DrawText("Press ESC to exit", 210, screenHeight / 2 + 30, 20, DARKGRAY);
		}

		EndDrawing();
	}

	CloseWindow();
}
