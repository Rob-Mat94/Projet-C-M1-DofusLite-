#include "../includes/ObjetRamassable.h"

ObjetRamassable::ObjetRamassable(Position pos) : Element(pos) {}

ObjetRamassable::~ObjetRamassable() {}

bool ObjetRamassable::element_action(Element *e)
{
    Guerrier *g = dynamic_cast<Guerrier *>(e);
    if (g != nullptr)
        this->pickUpElement(g);
    return true;
}