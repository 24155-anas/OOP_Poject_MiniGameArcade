#pragma once
class ttt_Player {
protected:
    char symbol;
public:
    ttt_Player(char s);
    virtual void makeMove(class ttt_Board& board) = 0;
    char getSymbol() const;
};
