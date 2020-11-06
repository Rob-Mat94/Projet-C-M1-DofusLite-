#include "../includes/Element.h"

Element::Element(Position pos):_pos(pos){}

Element::~Element(){}

void Element::setPosition(const Position &pos)
{
    this->_pos = pos;
}

Position& Element::getPosition()
{
    return this->_pos;
}