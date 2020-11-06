#ifndef ELEMENT_H
#define ELEMENT_H

#include "Position.h"

class Element
{   
    public :
        Element(Position pos = Position(0,0));
        Element(const Element& element);
        virtual ~Element();

    protected:
        Position _pos;
        virtual void setPosition(const Position &pos);
        virtual Position& getPosition();
};

#endif