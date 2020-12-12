#include "../includes/ObjetRamassable.h"

ObjetRamassable::ObjetRamassable(Position pos) : Element(pos) {}

ObjetRamassable::~ObjetRamassable() {}

bool ObjetRamassable::element_action()
{
    return false;
}