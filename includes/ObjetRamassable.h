#ifndef OBJECT_RAMASSABLE_H
#define OBJECT_RAMASSABLE_H
#include "Element.h"
#include "Guerrier.h"

class Guerrier;

class ObjetRamassable : public Element
{
public:
    ObjetRamassable(const int hp, Position pos = Position(0, 0));
    virtual ~ObjetRamassable();
    virtual bool element_action();

    const int getHpToGive() const { return _hp_to_give; }

    /* Représentation (caractère pour l'instant) */
    char getDraw() { return _hp_to_give + '0'; }
    virtual bool isEmpty() { return true; }
    virtual bool isPickable(){ return true; }

    virtual void pickUp(Guerrier *g);

private:
    const int _hp_to_give;
};

#endif