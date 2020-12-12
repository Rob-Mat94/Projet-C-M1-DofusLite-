#ifndef POTION_H
#define POTION_H
#include "ObjetRamassable.h"

class Potion : public ObjetRamassable
{
public:
    Potion(const int hp, Position pos = Position(0, 0));
    virtual ~Potion();

    const int getHpToGive() const { return _hp_to_give; }

    /* Méthodes héritées */
    /* Représentation (caractère pour l'instant) */
    char getDraw() { return _hp_to_give + '0'; }
    void pickUpElement(Guerrier *g);

private:
    const int _hp_to_give;
};

#endif