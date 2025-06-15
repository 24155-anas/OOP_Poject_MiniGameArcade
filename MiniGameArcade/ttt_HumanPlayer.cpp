#include "ttt_HumanPlayer.h"
#include "ttt_InvalidMoveException.h"

//ye wala func wothout graphics me use hoga 
void ttt_HumanPlayer::makeMove(ttt_Board& board) {
    int x, y;
   while (true) {
        cout << "Enter row and column (0-2): ";
        cin >> x >> y;
        try {
            board.placeMove(x, y, symbol);
            break;
        }
        catch (const ttt_InvalidMoveException& e) {
            cout << e.what() << endl;
        }
    }
}