#include "ttt_Player.h"

ttt_Player::ttt_Player(char s) : symbol(s) {}

char ttt_Player::getSymbol() const { 
	return symbol; 
}
