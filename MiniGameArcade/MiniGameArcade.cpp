#include "MiniGameArcade.h"
#include "ttt_GM.h"
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


enum MenuState {
    LOADING,
    MAIN_MENU,
    GAME_RULES,
    PLAYING_GAME,
    EXITING
};

enum GameType {
    CHESS = 0,
    TIC_TAC_TOE = 1,
    REVERSI = 2,
    RULES = 3,
    EXIT = 4
};

MiniGameArcade::MiniGameArcade() {
}

//graphics ka basic rule
//first take the input
//update your logic
// then design
void MiniGameArcade::runArcade() {
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Mini Game Arcade");
    SetTargetFPS(60);


    MenuState currentState = LOADING;
    GameType selectedGame = CHESS;
    float loadingProgress = 0.0f;
    int selectedButton = 0;
    float animationTimer = 0.0f;
    bool mouseHover[5] = { false, false, false, false, false };

    //colors
    Color backgroundColor = { 15, 15, 35, 255 };
    Color accentColor = { 255, 107, 107, 255 };
    Color buttonColor = { 45, 45, 75, 255 };
    Color buttonHoverColor = { 65, 65, 95, 255 };
    Color textColor = { 255, 255, 255, 255 };
    Color glowColor = { 255, 107, 107, 100 };

    vector<string> gameNames = { "Chess", "Tic Tac Toe", "Reversi", "Game Rules", "Exit" };
    vector<string> gameDescriptions = {
        "Classic strategy game",
        "3x3 grid challenge",
        "Flip to win",
        "Learn how to play",
        "Leave the arcade"
    };


    while (!WindowShouldClose()) {

        animationTimer += GetFrameTime();
        Vector2 mousePos = GetMousePosition();

        switch (currentState) {
        case LOADING: {
            loadingProgress += GetFrameTime() * 0.5f;
            if (loadingProgress >= 1.0f) {
                currentState = MAIN_MENU;
            }
            break;
        }

        case MAIN_MENU: {

            for (int i = 0; i < 5; i++) {
                Rectangle buttonRect = {
                    screenWidth / 2 - 200,
                    250 + i * 80,
                    400,
                    60
                };
                mouseHover[i] = CheckCollisionPointRec(mousePos, buttonRect);

                if (mouseHover[i] && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    selectedGame = (GameType)i;

                    switch (selectedGame) {
                    case CHESS:
                        currentState = PLAYING_GAME;
                        CloseWindow();
                        playChess();
                        return;
                        break;
                    case TIC_TAC_TOE:
                        currentState = PLAYING_GAME;
                        CloseWindow();
                        playTicTacToe();
                        return;
                    case REVERSI:
                        currentState = PLAYING_GAME;
                        CloseWindow();

                        playReversi();
                      
                        return;
                    case RULES:
                        currentState = GAME_RULES;
                        break;
                    case EXIT:
                        currentState = EXITING;
                        break;
                    }
                }
            }

            if (IsKeyPressed(KEY_UP)) selectedButton = (selectedButton - 1 + 5) % 5;
            if (IsKeyPressed(KEY_DOWN)) selectedButton = (selectedButton + 1) % 5;
            if (IsKeyPressed(KEY_ENTER)) {
                selectedGame = (GameType)selectedButton;
                //

            }

            break;
        }

        case GAME_RULES: {
            if (IsKeyPressed(KEY_ESCAPE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                currentState = MAIN_MENU;
            }
            break;
        }

        case EXITING: {
            break;
        }
        }

        if (currentState == EXITING) break;

        BeginDrawing();
        ClearBackground(backgroundColor);

        switch (currentState) {
        case LOADING: {
            //loading screen
            DrawText("MINI GAME ARCADE", screenWidth / 2 - 200, screenHeight / 2 - 100, 40, textColor);

            //loading bar
            Rectangle loadingBar = { screenWidth / 2 - 150, screenHeight / 2, 300, 20 };
            Rectangle loadingFill = { screenWidth / 2 - 150, screenHeight / 2, 300 * loadingProgress, 20 };

            DrawRectangleRounded(loadingBar, 0.5f, 10, { 50, 50, 50, 255 });
            DrawRectangleRounded(loadingFill, 0.5f, 10, accentColor);

            //dots
            string dots = "*";
            int dotCount = (int)(animationTimer * 7) % 4;
            for (int i = 0; i < dotCount; i++) dots += ".";
            DrawText(("Loading" + dots).c_str(), screenWidth / 2 - 50, screenHeight / 2 + 50, 20, textColor);

            break;
        }

        case MAIN_MENU: {
            //background particles
            for (int i = 0; i < 50; i++) {
                float x = fmod(i * 25 + sin(animationTimer + i) * 10, (float)screenWidth);
                float y = fmod(i * 15 + cos(animationTimer + i) * 5, (float)screenHeight);
                float alpha = sin(animationTimer + i) * 0.3f + 0.1f;
                DrawCircle((int)x, (int)y, 2, Fade(accentColor, alpha));
            }

            //title
            DrawText("MINI GAME ARCADE", screenWidth / 2 - 250, 100, 50, Fade(glowColor, 0.7f));
            DrawText("MINI GAME ARCADE", screenWidth / 2 - 252, 98, 50, textColor);

            //subtitle
            DrawText("Select Your Adventure", screenWidth / 2 - 120, 180, 20, Fade(textColor, 0.8f));

            //buttons
            for (int i = 0; i < 5; i++) {
                Rectangle buttonRect = {
                    screenWidth / 2 - 200,
                    250 + i * 80,
                    400,
                    60
                };

                Color currentButtonColor = buttonColor;
                if (mouseHover[i] || selectedButton == i) {
                    currentButtonColor = buttonHoverColor;

                    //hover effect/ jab buttons pe hover kro to glow 
                    DrawRectangleRounded({ buttonRect.x - 5, buttonRect.y - 5, buttonRect.width + 10, buttonRect.height + 10 }, 0.3f, 10, Fade(accentColor, 0.3f));
                }

                // Button with animation
                float scale = (mouseHover[i] || selectedButton == i) ? 1.05f : 1.0f;
                Rectangle animatedRect = {
                    buttonRect.x - (buttonRect.width * scale - buttonRect.width) / 2,
                    buttonRect.y - (buttonRect.height * scale - buttonRect.height) / 2,
                    buttonRect.width * scale,
                    buttonRect.height * scale
                };

                DrawRectangleRounded(animatedRect, 0.3f, 10, currentButtonColor);

                Color borderColor = (mouseHover[i] || selectedButton == i) ? accentColor : Fade(textColor, 0.3f);
                DrawRectangleRoundedLines(animatedRect, 0.3f, 10.0f, borderColor);

                //icons for games
                Vector2 iconPos = { buttonRect.x + 30, buttonRect.y + buttonRect.height / 2 };
                switch (i) {
                case 0: //chess k liye circle
                    DrawCircle(iconPos.x, iconPos.y, 15, textColor);
                    break;
                case 1: // tic tac toe ki grid
                    DrawRectangleLines(iconPos.x - 10, iconPos.y - 10, 20, 20, textColor);
                    DrawLine(iconPos.x - 3, iconPos.y - 10, iconPos.x - 3, iconPos.y + 10, textColor);
                    DrawLine(iconPos.x + 3, iconPos.y - 10, iconPos.x + 3, iconPos.y + 10, textColor);
                    DrawLine(iconPos.x - 10, iconPos.y - 3, iconPos.x + 10, iconPos.y - 3, textColor);
                    DrawLine(iconPos.x - 10, iconPos.y + 3, iconPos.x + 10, iconPos.y + 3, textColor);
                    break;
                case 2: // reversi k liye bhi circles
                    DrawCircle(iconPos.x, iconPos.y, 12, textColor);
                    DrawCircle(iconPos.x, iconPos.y, 8, backgroundColor);
                    break;
                case 3: //rules k liye qs mark
                    DrawText("?", iconPos.x - 8, iconPos.y - 12, 24, textColor);
                    break;
                case 4: //X foe exit
                    DrawText("X", iconPos.x - 8, iconPos.y - 12, 24, textColor);
                    break;
                }

                //text inside buttons
                DrawText(gameNames[i].c_str(), buttonRect.x + 80, buttonRect.y + 12, 24, textColor);
                DrawText(gameDescriptions[i].c_str(), buttonRect.x + 80, buttonRect.y + 38, 16, Fade(textColor, 0.7f));
            }

            
            DrawText("Use mouse or arrow keys + ENTER to select", screenWidth / 2 - 180, screenHeight - 50, 16, Fade(textColor, 0.6f));

            break;
        }

        case GAME_RULES: {
            
            DrawText("GAME RULES", screenWidth / 2 - 100, 100, 30, textColor);

            DrawText("TIC TAC TOE:", 100, 200, 24, accentColor);
            DrawText("3x3 grid game for two players", 120, 240, 20, textColor);
            DrawText("Players alternate placing X's and O's", 120, 270, 20, textColor);
            DrawText("Get 3 in a row to win", 120, 300, 20, textColor);
            DrawText("First player is X, second is O", 120, 330, 20, textColor);

            DrawText("CHESS:", 100, 400, 24, accentColor);
            DrawText("Classic strategy game Teset Your mins", 120, 440, 20, textColor);

            DrawText("REVERSI:", 100, 520, 24, accentColor);
            DrawText("8x8 board strategy game! ", 120, 560, 20, textColor);

            DrawText("Press ESC or click anywhere to return", screenWidth / 2 - 150, screenHeight - 50, 16, Fade(textColor, 0.6f));

            break;
        }
        }

        EndDrawing();
    }


    CloseWindow();

    if (currentState == EXITING) {
        displayGoodbyeMessage();
    }
}


//ye saare ab console based ha /////////////
void MiniGameArcade::displayWelcomeMessage() const {
    cout << "\n" <<  "==========" << "\n";
    cout << "       WELCOME TO MINI GAME ARCADE!\n";
    cout << "           Have Fun Playing!\n";
    cout << "\n" << "==========" << "\n";
}

void MiniGameArcade::displayGoodbyeMessage() const {
    cout << "\n" << "==========" << "\n";
    cout << "Thanks for playing!\n";
    cout << "Come back soon!\n";
    cout << "\n" << "==========" << "\n";
}

void MiniGameArcade::playTicTacToe() {
  /*  cout << "\n" << string(30, '*') << "\n";
    cout << "    Starting Tic Tac Toe Game...\n";
    cout << string(30, '*') << "\n";

    ttt_HumanPlayer p1('O');
    ttt_HumanPlayer p2('X');
    ttt_GM TIC_TAC_TOE(&p1, &p2);

    char choice;
    do {
        TIC_TAC_TOE.playWithGraphics();
        cout << "Play again? (y/n): ";
        cin >> choice;
    } while (choice == 'y');*/


    // Initialize the Tic-Tac-Toe window
    const int gameWidth = 600;
    const int gameHeight = 600;
    InitWindow(gameWidth, gameHeight, "Tic-Tac-Toe");
    SetTargetFPS(60);

    // Create players and game manager
    ttt_HumanPlayer p1('X');
    ttt_HumanPlayer p2('O');
    ttt_GM game(&p1, &p2);

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        game.playWithGraphics();
        EndDrawing();
    }

    // Clean up
    CloseWindow();

}

void MiniGameArcade::playReversi() {
    reversi_Board REVERSI_GAME;

    reversi_Player* player1 = new reversi_HumanPlayer('O');
    reversi_Player* player2 = new reversi_HumanPlayer('X');

    REVERSI_GAME.setPlayers(player1, player2);
    REVERSI_GAME.playWithGraphics();

}
void MiniGameArcade::playChess() {
    chess_Board chessBoard;



    cout << "Choose game mode:\n";
    cout << "1. Console mode\n";
    cout << "2. Graphics mode\n";
    cout << "Enter choice (1 or 2): ";

    int choice;
    cin >> choice;

    if (choice == 2) {
        ChessGraphics graphics(&chessBoard);

        chessBoard.setGraphics(&graphics);

        chessBoard.playWithGraphics();
    }
    else {
        //sada console game
        chessBoard.play();
    }
}



void MiniGameArcade::displayMenu() const {
    cout << "\n" << "==========" << "\n";
    cout << "         GAME SELECTION MENU\n";
    cout << "\n" << "==========" << "\n";
    cout << "1. Chess\n";
    cout << "2. Tic Tac Toe\n";
    cout << "3. Reversi\n";
    cout << "4. Show Game Rules\n";
    cout << "5. Exit Arcade\n";
    cout << "\n" << "==========" << "\n";
    cout << "Enter your choice (1-5): ";
}

int MiniGameArcade::getUserChoice() const {
    int choice;
    cout << "Enter choice: 1-5\n";
    cin >> choice;

    while (choice < 1 || choice > 5) {
        cout << "Invalid choice! Enter again: ";
        cin >> choice;
    }

    return choice;
}

void MiniGameArcade::showGameRules(int gameChoice) const {
    cout << "\n" << "==========" << "\n";
        
    switch (gameChoice) {

        ////
    case 2:
        cout << "               TIC TAC TOE RULES\n";
        cout << "==================================================================" << "\n";
        cout << "* 3x3 grid game for two players\n";
        cout << "* Players alternate placing X's and O's\n";
        cout << "* Get 3 in a row (horizontal, vertical, diagonal) to win\n";
        cout << "* First player is X, second player is O\n";
        break;
    }

    cout << "\nPress Enter to continue...";
    cin.get();
}


