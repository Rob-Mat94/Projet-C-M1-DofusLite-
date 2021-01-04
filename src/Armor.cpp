#include "../includes/Armor.h"

Armor::Armor(const int stat, Position pos) : ObjetRamassable(pos), _stat(stat) {}

void Armor::pickUpElement(Guerrier *g) const
{
    g->boostDefense(_stat);
}