#include "../includes/Sword.h"

Sword::Sword(const int stat, Position pos) : ObjetRamassable(pos), _stat(stat) {}

void Sword::pickUpElement(Guerrier *g) const
{
    g->boostAttack(_stat);
}