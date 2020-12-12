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
    virtual bool element_action();

    /* Méthodes héritées */
    /* Représentation (caractère pour l'instant) */
    bool isEmpty() { return true; }
    void pickUpElement(Guerrier *g) = 0;
};

#endif