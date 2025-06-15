#include "ttt_InvalidMoveException.h"
ttt_InvalidMoveException::ttt_InvalidMoveException(const myString& msg) : message(msg) {}

myString ttt_InvalidMoveException::what() const {
    return message;
}
