#ifndef EMPTY_ELEMENT_H
#define EMPTY_ELEMENT_H

#include "Element.h"

class EmptyElement : public Element
{
public:
    EmptyElement(Position pos = Position(0, 0));

    bool element_action(Element *e);
    char getDraw() const;
    bool isEmpty() const;
};

#endif