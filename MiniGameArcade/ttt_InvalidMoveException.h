#pragma once
#include "myString.h"

class ttt_InvalidMoveException
{
private:
    myString message;

public:
    ttt_InvalidMoveException(const myString& msg);

    myString what() const;

};

