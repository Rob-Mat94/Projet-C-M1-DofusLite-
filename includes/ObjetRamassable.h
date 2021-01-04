#ifndef OBJECT_RAMASSABLE_H
#define OBJECT_RAMASSABLE_H
#include "Element.h"
#include "Guerrier.h"

class Guerrier;

class ObjetRamassable : public Element
{
public:
    ObjetRamassable(Position pos = Position(0, 0));
    virtual ~ObjetRamassable();

    virtual void pickUpElement(Guerrier *g) const = 0;

    virtual bool element_action(Element *e);
    virtual bool isEmpty() const { return true; }
};

#endif