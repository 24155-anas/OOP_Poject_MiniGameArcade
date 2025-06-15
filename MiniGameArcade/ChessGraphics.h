#pragma once
#include "raylib.h"
#include "chess_Board.h"
#include "chess_Piece.h"
#include <string>

class ChessGraphics {
private:
    static const int BOARD_SIZE = 640;
    static const int SQUARE_SIZE = 80;
    static const int BOARD_OFFSET_X = 50;
    static const int BOARD_OFFSET_Y = 50;
    static const int WINDOW_WIDTH = 740;
    static const int WINDOW_HEIGHT = 740;

    chess_Board* board;
    Font font;

    //colors
    Color lightSquareColor;
    Color darkSquareColor;
    Color highlightColor;
    Color backgroundColor;

    Position selectedSquare;
    bool hasSelection;

    Position screenToBoard(Vector2 mousePos);
    Vector2 boardToScreen(Position pos);
    void drawBoard();
    void drawPieces();
    void drawHighlights();
    void drawCoordinates();
    char getPieceSymbol(Piece* piece);
    Color getPieceColor(Piece* piece);
    bool isLightSquare(int row, int col);


    
    void drawGameStatus();

   
    Dynamic_array<Position> legalMovesToHighlight;  //ye add kia, stores all legal moves for a peice taake wo highlight hosake
    void drawLegalMoveHighlights();

    Dynamic_array<Position> captureMoves;
    void drawCaptureMoveHighlights();

public:
    ChessGraphics(chess_Board* gameBoard);
    ~ChessGraphics();

    bool initGraphics();
    void closeGraphics();
    bool shouldClose();

    void render();
    bool handleInput(Position& source, Position& destination);
    void showMessage(const string& message);
    void highlightSquare(Position pos);
    void clearHighlight();


    void showCenteredMessage(const string& message, Color color = WHITE);


};
