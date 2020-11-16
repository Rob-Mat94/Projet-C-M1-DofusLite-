#ifndef WEAPON_H
#define WEAPON_H

#include "Element.h"
#include "Guerrier.h"

/* Possibilité de faire plusieurs types d'arme : elles hériteront de cette classe */
class AttackObject : public Element
{
    public :
       // using Element::Element;
        AttackObject(const int stat = 15, Position pos = Position(0,0));
        virtual ~AttackObject();
        virtual const int getStat()const{return this->_Stat;}; 

        /********/
       
    protected :
        const int _Stat;
        
};

#endif