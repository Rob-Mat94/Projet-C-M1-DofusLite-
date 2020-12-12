#include "../includes/Sword.h"

Sword::Sword(const int stat, Position pos) : ObjetRamassable(pos), _stat(stat) {}

void Sword::pickUpElement(Guerrier *g)
{
    g->boostAttack(_stat);
}