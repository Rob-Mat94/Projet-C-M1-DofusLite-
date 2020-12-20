#ifndef ELEMENT_H
#define ELEMENT_H

#include "Position.h"
#include <string>

class Guerrier;

class Element
{
public:
    Element(Position pos = Position(0, 0));
    Element(const Element &element);
    virtual ~Element();

    virtual void setPosition(const Position &pos);
    virtual const Position &getPosition() const;
    virtual bool element_action(Element *e) = 0;
    virtual char getDraw() = 0;
    virtual bool isEmpty() = 0;

protected:
    Position _pos;
};

#endif