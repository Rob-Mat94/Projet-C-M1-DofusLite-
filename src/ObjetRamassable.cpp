#include "../includes/ObjetRamassable.h"

ObjetRamassable::ObjetRamassable(const int hp, Position pos) : Element(pos), _hp_to_give(hp) {}

ObjetRamassable::~ObjetRamassable() {}

bool ObjetRamassable::element_action()
{
    return true;
}

void ObjetRamassable::pickUp(Guerrier *g)
{
    g->setHp(_hp_to_give);
}