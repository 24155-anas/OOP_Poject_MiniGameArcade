#pragma once
class reversi_Player {
private:
	char symbol;
public:
	reversi_Player(char s);
	char getSymbol() const;
};