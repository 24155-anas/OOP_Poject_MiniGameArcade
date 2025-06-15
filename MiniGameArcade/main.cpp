#include "raylib.h"
#include "MiniGameArcade.h"
using namespace std;





int main1() {
    ttt_HumanPlayer p1('O');
    ttt_HumanPlayer p2('X');
    ttt_GM game(&p1, &p2);

    char choice;
    do {
        game.play();
        cout << "Play again? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    return 0;
}


int main() {
    MiniGameArcade arcade;
    arcade.runArcade();
    return 0;
}






