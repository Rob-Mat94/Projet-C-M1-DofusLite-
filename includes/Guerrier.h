#ifndef GUERRIER_H
#define GUERRIER_H

#include "Element.h"
#include <iostream>
#include "Direction.h"
#include "Carte.h"
#include <vector>

class Carte;
class Guerrier : public Element
{
public:
    Guerrier(const std::string equipe, Position pos = Position(0, 0),
             int hp = 100, std::string name = "default", int capAttack = 50, int capDef = 50);
    virtual ~Guerrier() = default;

    bool operator==(const Guerrier &g) const;

    /* Méthodes héritées */
    bool element_action(Element *e);
    bool isEmpty() { return false; }

    /* Représentation (caractère pour l'instant) */
    char getDraw();

    /****************/
    bool estAdversaire(Guerrier *g);
    bool move(Direction dir, Carte *c);

    void heal(int hp);
    void boostAttack(int stat);
    void boostDefense(int stat);
    bool Attack(Guerrier *g, Carte *c);
    void getAttacked(int capAttack, Carte *c);
    void die(Carte *c);

    /***  G / S  ***/
    const int getHp() const { return this->_hp; }
    void setHp(const int hp)
    {
        _hp = hp;
        if (_hp < 0)
            _hp = 0;
    }

    const std::string getName() const { return this->_name; }
    const std::string getTeam() const { return this->_team; }

    const int getCapAttack() const { return this->_capAttack; }
    void setCapAttack(const int cA) { this->_capAttack = cA; }

    int getCapDef() const { return this->_capDef; }
    void setCapDef(const int cD) { this->_capDef = cD; }

private:
    static std::vector<std::string> name_list;
    static int name_list_index;
    int _hp;
    const std::string _name;
    const std::string _team;
    int _capAttack;
    int _capDef;
};

#endif