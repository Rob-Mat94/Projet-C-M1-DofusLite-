#ifndef SWORD_H
#define SWORD_H
#include "ObjetRamassable.h"

class Sword : public ObjetRamassable
{
public:
    Sword(const int stat = 15, Position pos = Position(0, 0));
    virtual ~Sword() = default;

    const int getStat() const { return _stat; }
    char getDraw() { return 'S'; }

    void pickUpElement(Guerrier *g);

private:
    const int _stat;
};

#endif