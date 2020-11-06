#ifndef ELEMENT_H
#define ELEMENT_H

#include "Position.h"

class Element
{   
    public :
        Element(Position pos = Position(0,0));
        Element(const Element& element);
        virtual ~Element();

        /* Héritage */
        virtual void setPosition(const Position &pos);
        virtual const Position& getPosition()const;
        virtual void element_action() = 0; // Action de l'élément 

    protected:
        Position _pos;
};

#endif