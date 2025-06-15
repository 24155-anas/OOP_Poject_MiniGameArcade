
#include "ChessGraphics.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
using namespace std;

ChessGraphics::ChessGraphics(chess_Board* gameBoard) : board(gameBoard) {
    //colors
    lightSquareColor = { 240, 217, 181, 255 };  //Light tan
    darkSquareColor = { 181, 136, 99, 255 };    //Dark brown
    highlightColor = { 255, 255, 0, 128 };      //Semi-transparent yellow
    backgroundColor = { 50, 50, 50, 255 };      //Dark gray
    //shuru me koi square selectyed ni hoga

    hasSelection = false;
    selectedSquare = { -1, -1 };
}

ChessGraphics::~ChessGraphics() {
    if (IsWindowReady()) {
        CloseWindow();
    }
}

bool ChessGraphics::initGraphics() {

    InitWindow(WINDOW_WIDTH + 200, WINDOW_HEIGHT + 100, "Chess Game");
    SetTargetFPS(60);

    font = GetFontDefault();

    return !WindowShouldClose();
}



void ChessGraphics::closeGraphics() {
    if (IsWindowReady()) {
        CloseWindow();
    }
}

bool ChessGraphics::shouldClose() {
    return WindowShouldClose();
}

Color ChessGraphics::getPieceColor(Piece* piece) {
    return piece->getCOLOR() == WHITE_P ? WHITE : BLACK;
}

bool ChessGraphics::isLightSquare(int row, int col) {

    return (row + col) % 2 == 0;
}


void ChessGraphics::highlightSquare(Position pos) {
    selectedSquare = pos;
    hasSelection = true;
}

void ChessGraphics::clearHighlight() {
    hasSelection = false;
}

void ChessGraphics::render() {
    BeginDrawing();
    ClearBackground(backgroundColor);

    drawBoard();
    drawHighlights();
    drawLegalMoveHighlights();
    drawCaptureMoveHighlights();
    drawPieces();
    drawCoordinates();
    drawGameStatus();

    EndDrawing();
}

void ChessGraphics::drawBoard() {
    //board ki drawing
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Color squareColor = isLightSquare(row, col) ? lightSquareColor : darkSquareColor;

            Rectangle square = {
                BOARD_OFFSET_X + col * SQUARE_SIZE,
                BOARD_OFFSET_Y + row * SQUARE_SIZE,
                SQUARE_SIZE,
                SQUARE_SIZE
            };

            DrawRectangleRec(square, squareColor);
            DrawRectangleLinesEx(square, 1, BLACK);
        }
    }
}

void ChessGraphics::drawPieces() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* piece = board->getPiece(Position{ row, col });
            if (piece != nullptr) {
                Vector2 pos = boardToScreen({ row, col });
                char symbol = getPieceSymbol(piece);
                Color color = getPieceColor(piece);

                //pieces as letters
                string pieceStr(1, symbol);
                Vector2 textSize = MeasureTextEx(font, pieceStr.c_str(), 48, 1);
                Vector2 textPos = {
                    pos.x + (SQUARE_SIZE - textSize.x) / 2,
                    pos.y + (SQUARE_SIZE - textSize.y) / 2
                };

                //2 itmes banao for shadow effect
                DrawTextEx(font, pieceStr.c_str(), { textPos.x + 2, textPos.y + 2 }, 48, 1, BLACK);
                DrawTextEx(font, pieceStr.c_str(), textPos, 48, 1, color);
            }
        }
    }
}

//for highlighting a square
void ChessGraphics::drawHighlights() {
    if (hasSelection) {
        Vector2 pos = boardToScreen(selectedSquare);
        Rectangle highlight = { pos.x, pos.y, SQUARE_SIZE, SQUARE_SIZE };
        DrawRectangleRec(highlight, highlightColor);
    }
}

void ChessGraphics::drawCoordinates() {
    //row num 1-8
    for (int row = 0; row < 8; row++) {
        string rowStr = to_string(8 - row);
        DrawText(rowStr.c_str(),
            BOARD_OFFSET_X - 25,
            BOARD_OFFSET_Y + row * SQUARE_SIZE + SQUARE_SIZE / 2 - 10,
            20, WHITE);
        DrawText(rowStr.c_str(),
            BOARD_OFFSET_X + BOARD_SIZE + 5,
            BOARD_OFFSET_Y + row * SQUARE_SIZE + SQUARE_SIZE / 2 - 10,
            20, WHITE);
    }

    //letters a-h
    const char* colLetters = "abcdefgh";
    for (int col = 0; col < 8; col++) {
        string colStr(1, colLetters[col]);
        DrawText(colStr.c_str(),
            BOARD_OFFSET_X + col * SQUARE_SIZE + SQUARE_SIZE / 2 - 5,
            BOARD_OFFSET_Y - 25,
            20, WHITE);
        DrawText(colStr.c_str(),
            BOARD_OFFSET_X + col * SQUARE_SIZE + SQUARE_SIZE / 2 - 5,
            BOARD_OFFSET_Y + BOARD_SIZE + 5,
            20, WHITE);
    }
}
void ChessGraphics::drawGameStatus() {
    //top me turn indicator
    string turnMsg = (board->getTurn() == WHITE_P) ? "White's turn" : "Black's turn";
    Vector2 turnSize = MeasureTextEx(font, turnMsg.c_str(), 30, 1);
    Vector2 turnPos = {
        (WINDOW_WIDTH - turnSize.x) / 2,
        10
    };
    DrawTextEx(font, turnMsg.c_str(), turnPos, 30, 1, WHITE);

    //status texts
    if (board->isCheckMate(WHITE_P)) {
        showCenteredMessage("CHECKMATE! Black wins", RED);
    }
    else if (board->isCheckMate(BLACK_P)) {
        showCenteredMessage("CHECKMATE! White wins", RED);
    }
    else if (board->isCheck(WHITE_P)) {
        showCenteredMessage("White is in CHECK!", YELLOW);
    }
    else if (board->isCheck(BLACK_P)) {
        showCenteredMessage("Black is in CHECK!", YELLOW);
    }
    else if (board->isStaleMate(WHITE_P) || board->isStaleMate(BLACK_P)) {
        showCenteredMessage("STALEMATE game is draw!",RED);
    }
}

void ChessGraphics::showCenteredMessage(const string& message, Color color) {
    Vector2 textSize = MeasureTextEx(font, message.c_str(), 30, 1);
    Vector2 pos = {
        (WINDOW_WIDTH - textSize.x) / 2,
        BOARD_OFFSET_Y + BOARD_SIZE + 30
    };

    //backgound rect
    Rectangle bgRect = { pos.x - 10, pos.y - 5, textSize.x + 20, textSize.y + 10 };
    DrawRectangleRec(bgRect, BLACK);
    DrawRectangleLinesEx(bgRect, 2, WHITE);

    DrawTextEx(font, message.c_str(), pos, 30, 1, color);
}




bool ChessGraphics::handleInput(Position& source, Position& destination) {

    if (board->isCheckMate(WHITE_P) || board->isCheckMate(BLACK_P)) {
        return false;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        Position clickedPos = screenToBoard(mousePos);

        //bounds check
        if (clickedPos.row_i >= 0 && clickedPos.row_i < 8 && clickedPos.col_i >= 0 && clickedPos.col_i < 8) {

            if (!hasSelection) {
                //peg=hle click me source
                source = clickedPos;
                selectedSquare = clickedPos;
                hasSelection = true;
                this->legalMovesToHighlight = board->getLegalMoves(clickedPos);
                this->captureMoves = board->getCaptureMoves(clickedPos);
                return false;
            }
            else {
                //dosre click me destinantion
                destination = clickedPos;
                hasSelection = false;
                this->legalMovesToHighlight.clear();
                this->captureMoves.clear();
                return true; //ab true return kro for completion pf move
            }
        }
    }

    //agr right click then clear the selection
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        hasSelection = false;
        this->legalMovesToHighlight.clear();

    }

    return false;
}
void ChessGraphics::showMessage(const std::string& message) {
    Vector2 textSize = MeasureTextEx(font, message.c_str(), 24, 1);
    Vector2 pos = {
        (WINDOW_WIDTH - textSize.x) / 2,
        WINDOW_HEIGHT - 40
    };

    //rect in background 
    Rectangle bgRect = { pos.x - 10, pos.y - 5, textSize.x + 20, textSize.y + 10 };
    DrawRectangleRec(bgRect, BLACK);
    DrawRectangleLinesEx(bgRect, 2, WHITE);

    DrawTextEx(font, message.c_str(), pos, 24, 1, WHITE);
}


//convert screen pos to board
Position ChessGraphics::screenToBoard(Vector2 mousePos) {
    int col = (mousePos.x - BOARD_OFFSET_X) / SQUARE_SIZE;
    int row = (mousePos.y - BOARD_OFFSET_Y) / SQUARE_SIZE;
    Position boardPos;
    boardPos.row_i = row;
    boardPos.col_i = col;
    return boardPos;
}

//cpnvert board pos to screen
Vector2 ChessGraphics::boardToScreen(Position pos) {
    Vector2 screenPos;
    screenPos.x = BOARD_OFFSET_X + pos.col_i * SQUARE_SIZE;
    screenPos.y = BOARD_OFFSET_Y + pos.row_i * SQUARE_SIZE;
    return screenPos;
}

char ChessGraphics::getPieceSymbol(Piece* piece) {
    //dynamic casting use ki ha to determine piece type
    if (dynamic_cast<Queen*>(piece)) {
        return piece->getCOLOR() == WHITE_P ? 'Q' : 'q';
    }
    else if (dynamic_cast<King*>(piece)) {
        return piece->getCOLOR() == WHITE_P ? 'K' : 'k';
    }
    else if (dynamic_cast<Pawn*>(piece)) {
        return piece->getCOLOR() == WHITE_P ? 'P' : 'p';
    }
    else if (dynamic_cast<Rook*>(piece)) {
        return piece->getCOLOR() == WHITE_P ? 'R' : 'r';
    }
    else if (dynamic_cast<Horse*>(piece)) {
        return piece->getCOLOR() == WHITE_P ? 'N' : 'n';
    }
    else if (dynamic_cast<Bishop*>(piece)) {
        return piece->getCOLOR() == WHITE_P ? 'B' : 'b';
    }


    return '?';
}





void ChessGraphics::drawLegalMoveHighlights() {
    Color highlightColor = { 0, 255, 0, 100 };

    
    for (int i = 0; i < legalMovesToHighlight.size(); i++) {
        Position pos = legalMovesToHighlight[i];
        Vector2 screenPos = boardToScreen(pos);
        Rectangle highlight = { screenPos.x, screenPos.y, SQUARE_SIZE, SQUARE_SIZE };
        DrawRectangleRec(highlight, highlightColor);
    }
}

void ChessGraphics::drawCaptureMoveHighlights() {
    Color highlightColor = { 255, 0, 0, 150 };; //redd


    for (int i = 0; i < captureMoves.size(); i++) {
        Position pos = captureMoves[i];
        Vector2 screenPos = boardToScreen(pos);
        Rectangle highlight = { screenPos.x, screenPos.y, SQUARE_SIZE, SQUARE_SIZE };
        DrawRectangleRec(highlight, highlightColor);
    }
}
