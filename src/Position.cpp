#include "../includes/Position.h"

Position::Position(int x, int y)
{
    setPosX(x);
    setPosY(y);
}

Position::~Position() {}

Position::Position(const Position &pos)
{
    setPosX(pos._x);
    setPosY(pos._y);
}

bool Position::operator==(const Position &p)const
{
    if(this->_x == p._x && this->_y == p._y)
        return true;
    return false;
}

int Position::getPosX() const
{
    return this->_x;
}

int Position::getPosY() const
{
    return this->_y;
}

void Position::setPosX(const int x)
{
    if (x >= 0)
        this->_x = x;
}

void Position::setPosY(const int y)
{
    if (y >= 0)
        this->_y = y;
}