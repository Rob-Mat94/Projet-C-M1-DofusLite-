#include "../includes/EmptyElement.h"

EmptyElement::EmptyElement(Position pos) : Element(pos) {}

bool EmptyElement ::element_action(Element *e)
{
    return false;
}

char EmptyElement::getDraw() const
{
    return ' ';
}

bool EmptyElement::isEmpty() const
{
    return true;
}