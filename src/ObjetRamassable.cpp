#include "../includes/ObjetRamassable.h"

ObjetRamassable::ObjetRamassable(const int hp, Position pos) : Element(pos), _hp_to_give(hp) {}

ObjetRamassable::~ObjetRamassable() {}

bool ObjetRamassable::element_action()
{
    return true;
}