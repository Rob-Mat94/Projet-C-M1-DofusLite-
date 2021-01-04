#ifndef ARMOR_H
#define ARMOR_H
#include "ObjetRamassable.h"

class Armor : public ObjetRamassable
{
public:
    Armor(const int stat = 15, Position pos = Position(0, 0));
    virtual ~Armor() = default;

    const int getStat() const { return _stat; }
    char getDraw() const { return 'A'; }

    void pickUpElement(Guerrier *g) const;

private:
    const int _stat;
};

#endif