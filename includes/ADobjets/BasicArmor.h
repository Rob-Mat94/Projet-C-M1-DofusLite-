#ifndef BASICARMOR_H
#define BASICARMOR_H
#include "../AttackObject.h"

class BasicArmor : public AttackObject
{
    using AttackObject :: AttackObject;
    char getDraw(){return 'A';}
    void pickUpElement(Guerrier *g)
    {
        g->setCapDef(g->getCapDef() + this->_Stat);
    }


};

#endif