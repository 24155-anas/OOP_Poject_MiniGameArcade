#include "reversi_Player.h"


reversi_Player::reversi_Player(char s) : symbol(s) {}
char reversi_Player::getSymbol() const {
	return symbol;
}