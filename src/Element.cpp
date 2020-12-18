#include "../includes/Element.h"

Element::Element(Position pos) : _pos(pos) {}

Element::Element(const Element &element) : _pos(element._pos) {}

Element::~Element() {}

void Element::setPosition(const Position &pos)
{
    this->_pos = pos;
}

// représente ' '(vide) pour l'instant
bool Element ::element_action()
{
    return false;
}

const Position &Element::getPosition() const
{
    return this->_pos;
}

