#ifndef SWORD_H
#define SWORD_H
#include "ObjetRamassable.h"

class Sword : public ObjetRamassable
{
public:
    Sword(const int stat = 15, Position pos = Position(0, 0));
    virtual ~Sword() = default;

    const int getStat() const { return _stat; }
    char getDraw() const { return 'S'; }

    void pickUpElement(Guerrier *g) const;

private:
    const int _stat;
};

#endif