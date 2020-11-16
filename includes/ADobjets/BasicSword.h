#ifndef BASICSWORD_H
#define BASICSWORD_H
#include "../AttackObject.h"

class BasicSword : public AttackObject
{
    using AttackObject :: AttackObject;
    char getDraw(){return 'S';}
    void pickUpElement(Guerrier *g)
    {
        g->setCapAttack(g->getCapAttack() + this->_Stat);
    }


};

#endif