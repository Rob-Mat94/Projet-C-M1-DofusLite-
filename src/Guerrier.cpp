#include "../includes/Guerrier.h"



std::vector<std::string> Guerrier::name_list = {"Gareth","Lancelot","Arthur","Perceval","Léodagan","Yvain","Robert","Sagremor"};
int Guerrier::name_list_index = 0;

Guerrier::Guerrier(const std::string team, Position pos, int hp, std::string name, int capAttack, int capDef)
    : Element(pos), _hp(hp), _name(name_list[name_list_index]), _team(team), _capAttack(capAttack), _capDef(capDef) {name_list_index++;}

bool Guerrier::estAdversaire(Guerrier *g)
{
    if (g->getTeam() == this->_team)
        return false;
    return true;
}

char Guerrier::getDraw()
{
    if (_team == "team 1")
        return 'G';
    else
        return 'g';
}

bool Guerrier::operator==(const Guerrier &g) const
{
    if (this->_pos == g._pos)
        return true;
    return false;
}

bool Guerrier::element_action()
{
    return true;
}

bool Guerrier::move(Direction dir, Carte *carte)
{
    Coordinate c = getDirCoordinate(dir);
    Position oldPos = this->_pos;
    Position newPos = Position(_pos.getPosX() + c.x, _pos.getPosY() + c.y);

    if (carte->updatePos(this, oldPos, newPos))
    {
        setPosition(newPos);
        return true;
    }

    return false;
}

// methodes liés aux objets ramassables (potions, armes, et armures)
void Guerrier::heal(int hp)
{
    this->setHp(_hp + hp);
}

void Guerrier::boostAttack(int stat)
{
    this->setCapAttack(_capAttack + stat);
}

void Guerrier::boostDefense(int stat)
{
    this->setCapDef(_capDef + stat);
}

bool Guerrier::Attack(Guerrier *g, Carte *c)
{
    if (g == nullptr)
        return false;
    g->getAttacked(this->_capAttack, c);
    return true;
}

void Guerrier::getAttacked(int damages, Carte *c)
{
    int dmg = this->_capDef - damages;
    if (dmg < 0)
    {
        setCapDef(0);
        setHp(_hp + dmg);
    }
    else
    {
        setCapDef(dmg);
    }
    if (_hp <= 0)
    {
        this->die(c);
    }
}

void Guerrier::die(Carte *c)
{
    c->removeElement(this);
}