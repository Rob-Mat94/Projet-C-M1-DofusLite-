#ifndef GUERRIER_H
#define GUERRIER_H

#include "Position.h"
#include "Element.h"
#include <string>
#include <iostream>

class Guerrier : public Element
{
    public:
        Guerrier(const std::string equipe,Position pos = Position(0,0),int hp = 100, std::string name = "default", int capAttack = 50, int capDef = 50);
        virtual ~Guerrier();
        void element_action();

        /***  G / S  ***/ 
        const int getHp()const{return this->_hp;}
        void setHp(const int hp){this->_hp = hp;}
        const std::string getName()const{return this->_name;}
        const std::string getTeam()const{return this->_team;}
        int getCapAttack()const{return this->_capAttack;}
        void setCapAttack(const int cA){this->_capAttack = cA;}
        int getCapDef()const{return this->_capDef;}
        void setCapDef(const int cD){this->_capDef = cD;}

        /* Représentation (caractère pour l'instant) */
        char getDraw(){
            if(_team == "team 1")
                return 'G';
            else
                return 'g';
        }

    private:
        int _hp; 
        const std::string _name;
        const std::string _team;
        int _capAttack;
        int _capDef;

};

#endif