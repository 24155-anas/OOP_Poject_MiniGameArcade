#include "ttt_GM.h"


ttt_GM::ttt_GM(ttt_Player* p1, ttt_Player* p2) : turn(0) {
    players[0] = p1;
    players[1] = p2;
}

//without graphics
void ttt_GM::play() {
    board.reset();
    while (true) {
        board.display();
        players[turn]->makeMove(board);
        if (board.checkWinner(players[turn]->getSymbol())) {
            board.display();
            cout << "Player " << players[turn]->getSymbol() << " wins!" << endl;
            break;
        }
        if (board.isDraw()) {
            board.display();
            cout << "It's a draw!" << endl;
            break;
        }
        turn_change();
    }
}

void ttt_GM::turn_change() {
    this->turn = (this->turn + 1) % 2;
}

void ttt_GM::playWithGraphics() {

    const int screenWidth = 500;
    const int screenHeight = 500;
    const int cellSize = screenWidth / 3;
    const int padding = 20;
    const int lineThickness = 8;

    // Color struct ha raylib me {r,g,b,a}
    Color backgroundColor = { 25, 25, 45, 255 };//dark blueish background
    Color gridColor = { 200, 200, 200, 255 };//light gray
    Color xColor = { 255, 80, 80, 255 };//red
    Color oColor = { 80, 180, 255, 255 };//blue
    Color highlightColor = { 100, 255, 100, 100 };//green
    Color textColor = { 255, 255, 255, 255 };//white
    Color shadowColor = { 0, 0, 0, 150 };//blackish

    //saari screen ka backgroung color hojayega isse
    ClearBackground(backgroundColor);

    //drawing of grid 
    for (int i = 1; i < 3; i++) {
        
        // SYntax :: DrawRectangle(x, y, width, height, color)
        // ye vertical lines hain
        DrawRectangle(i * cellSize - lineThickness / 2 + 2, padding + 2, lineThickness, screenHeight - 2 * padding, shadowColor);
        DrawRectangle(i * cellSize - lineThickness / 2, padding, lineThickness, screenHeight - 2 * padding, gridColor);

        //ye horizontal loines with shadow
        DrawRectangle(padding + 2, i * cellSize - lineThickness / 2 + 2, screenWidth - 2 * padding, lineThickness, shadowColor);
        DrawRectangle(padding, i * cellSize - lineThickness / 2, screenWidth - 2 * padding, lineThickness, gridColor);
    }

    //hovering animation
    //Vector2 is a struct x, y
    // getmousePosition return the index clicked by mouse

    Vector2 mousePos = GetMousePosition();
    //divide by cellsize taake pata chale kis cell pe hai
    int hoverX = mousePos.x / cellSize;
    int hoverY = mousePos.y / cellSize;

    if (hoverX >= 0 && hoverX < 3 && hoverY >= 0 && hoverY < 3 && board.isEmpty(hoverX, hoverY) && !board.checkWinner(players[turn]->getSymbol()) && !board.isDraw()) {

       /* Raylib’s Fade() function adjusts the alpha(transparency) of a color.So Fade(oColor, pulse) means
       When pulse is 0.3::more transparent
       When pulse is 0.7::more solid.*/

        //sin -1 see 1 k beech walue dega
        //Gettime wo time dega jab se game start hoi ha
        float pulse = 0.5f + 0.2f * sin(4 * GetTime());
        Rectangle hoverRect;
        hoverRect.x = hoverX * cellSize + padding / 2.0f;
        hoverRect.y = hoverY * cellSize + padding / 2.0f;
        hoverRect.width = cellSize - padding;
        hoverRect.height = cellSize - padding;

        //draws a rounded rect
        //DrawRectangleRounded(rect, roundness, segments, color)
        DrawRectangleRounded(hoverRect, 0.2f, 12, Fade(oColor, pulse));

    }


    //Drawing symbols
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char cell = board.getCell(i, j);
            float centerX = i * cellSize + cellSize / 2;
            float centerY = j * cellSize + cellSize / 2;
            float radius = cellSize / 2 - padding;

            if (cell == 'X') {
                float offset = radius * 0.7f;
                float thickness = 10.0f;

                //DrawLineEx(startVec2, endVec2, thickness, color);
                DrawLineEx(Vector2{ centerX - offset + 2, centerY - offset + 2 }, Vector2{ centerX + offset + 2, centerY + offset + 2 }, thickness, shadowColor);
                DrawLineEx(Vector2{ centerX + offset + 2, centerY - offset + 2 }, Vector2{ centerX - offset + 2, centerY + offset + 2 }, thickness, shadowColor);

                DrawLineEx(Vector2{ centerX - offset, centerY - offset }, Vector2{ centerX + offset, centerY + offset }, thickness - 2, xColor);
                DrawLineEx(Vector2{ centerX + offset, centerY - offset }, Vector2{ centerX - offset, centerY + offset }, thickness - 2, xColor);
            }
            else if (cell == 'O') {
                float thick = 6.0f;
                for (float i = 0; i < thick; i++) {
                    //DrawCircleLines(centerX, centerY, radius, color);
                    DrawCircleLines(centerX + 2, centerY + 2, radius - i, shadowColor);
                    DrawCircleLines(centerX, centerY, radius - i, oColor);
                }
            }

        }
    }

    //checking winner or draw
    if (board.checkWinner(players[turn]->getSymbol())) {
        //pore scren pr aik rectangle banado jo darken krdega screen k0
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));

        //text for winner
        const char* text = TextFormat("Player %d (%c) Wins!", turn + 1, players[turn]->getSymbol());
        int textWidth = MeasureText(text, 50);

        //DrawText(text, x, y, fontSize, color);
        DrawText(text, screenWidth / 2 - textWidth / 2 + 3, screenHeight / 2 - 25 + 3, 50, shadowColor);
        DrawText(text, screenWidth / 2 - textWidth / 2, screenHeight / 2 - 25, 50, (turn == 0) ? xColor : oColor);

        // Play again prompt
        const char* prompt = "Click anywhere to continue";
        int promptWidth = MeasureText(prompt, 30);
        DrawText(prompt, screenWidth / 2 - promptWidth / 2 + 2, screenHeight / 2 + 40 + 2, 30, shadowColor);
        DrawText(prompt, screenWidth / 2 - promptWidth / 2, screenHeight / 2 + 40, 30, textColor);

        //mouse se kahi bhi click kroge to board reset hojayega 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            board.reset();
        }
    }
    else if (board.isDraw()) {
        //pore scren pr aik rectangle banado jo darken krdega screen k0
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));

        const char* text = "It's a Draw!";
        int textWidth = MeasureText(text, 50);

        DrawText(text, screenWidth / 2 - textWidth / 2 + 3, screenHeight / 2 - 25 + 3, 50, shadowColor);
        DrawText(text, screenWidth / 2 - textWidth / 2, screenHeight / 2 - 25, 50, textColor);

        const char* prompt = "Click anywhere to continue";
        int promptWidth = MeasureText(prompt, 30);
        DrawText(prompt, screenWidth / 2 - promptWidth / 2 + 2, screenHeight / 2 + 40 + 2, 30, shadowColor);
        DrawText(prompt, screenWidth / 2 - promptWidth / 2, screenHeight / 2 + 40, 30, textColor);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            board.reset();
        }
    }
    else {
           //handlw the input of mouse
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int x = mousePos.x / cellSize;
            int y = mousePos.y / cellSize;

            if (x >= 0 && x < 3 && y >= 0 && y < 3 && board.isEmpty(x, y)) {
                board.placeMove(x, y, players[turn]->getSymbol());

                if (!board.checkWinner(players[turn]->getSymbol()) && !board.isDraw()) {
                    turn_change();
                }
            }
        }
        const char* turnText = TextFormat("Player %d's Turn (%c)", turn + 1, players[turn]->getSymbol());
        int textWidth = MeasureText(turnText, 30);
        DrawText(turnText, screenWidth / 2 - textWidth / 2, 20, 30, (turn == 0) ? xColor : oColor);
    }
}