#include "../includes/Position.h"

Position::Position(int x, int y):_x(x),_y(y){}

Position::~Position(){}

Position::Position(const Position &pos)
{
    this->_x = pos._x;
    this->_y = pos._y;
}

int Position::getPosX()const
{
    return this->_x;
}

int Position::getPosY()const
{
    return this->_y;
}

void Position::setPosX(const int x)
{
    if(x >= 0)
        this->_x = x;
}

void Position::setPosY(const int y)
{
    if(y >= 0)
        this->_y = y;
}