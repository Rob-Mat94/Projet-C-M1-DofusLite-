#ifndef ELEMENT_H
#define ELEMENT_H

#include "Position.h"

class Element
{
public:
    Element(Position pos = Position(0, 0));
    Element(const Element &element);
    virtual ~Element();

    /* Héritage */
    virtual void setPosition(const Position &pos);
    virtual const Position &getPosition() const;
    virtual bool element_action(); // Action de l'élément
    /* Représentation (caractère pour l'instant) */
    virtual char getDraw() { return ' '; }

protected:
    Position _pos;
};

#endif