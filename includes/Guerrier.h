#ifndef GUERRIER_H
#define GUERRIER_H

#include "Element.h"
#include <iostream>
#include "Direction.h"
#include "Carte.h"

class Carte;
class Guerrier : public Element
{
public:
    Guerrier(const std::string equipe, Position pos = Position(0, 0),
             int hp = 100, std::string name = "default", int capAttack = 50, int capDef = 50);
    virtual ~Guerrier();

    bool operator==(const Guerrier &g)const;

    /* Méthodes héritées */
    bool element_action();
    bool isEmpty() { return false; }
    /* Représentation (caractère pour l'instant) */
    char getDraw();

    /****************/
    bool Attack(Guerrier* g);

    bool estAdversaire(Guerrier *g);
    bool move(Direction dir, Carte &c);
    /***  G / S  ***/
    const int getHp() const { return this->_hp; }
    void setHp(const int hp) { this->_hp = hp; }
    const std::string getName() const { return this->_name; }
    const std::string getTeam() const { return this->_team; }
    const int getCapAttack() const { return this->_capAttack; }
    void setCapAttack(const int cA) { this->_capAttack = cA; }
    int getCapDef() const { return this->_capDef; }
    void setCapDef(const int cD) { this->_capDef = cD; }

private:
    int _hp;
    const std::string _name;
    const std::string _team;
    int _capAttack;
    int _capDef;
};

#endif