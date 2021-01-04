#include "../includes/Potion.h"

Potion::Potion(const int hp, Position pos) : ObjetRamassable(pos), _hp_to_give(hp) {}

Potion::~Potion() = default;

void Potion::pickUpElement(Guerrier *g) const
{
    g->heal(_hp_to_give);
}