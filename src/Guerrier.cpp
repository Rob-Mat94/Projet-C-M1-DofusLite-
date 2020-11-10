#include "../includes/Guerrier.h"

Guerrier::Guerrier(const std::string team, Position pos, int hp, std::string name, int capAttack, int capDef)
    : Element(pos), _hp(hp), _name(name), _team(team), _capAttack(capAttack), _capDef(capDef) {}

Guerrier::~Guerrier() {}

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

bool Guerrier::operator==(const Guerrier &g)const
{
    if(this->_pos == g._pos)
        return true;
    return false;
}

bool Guerrier::element_action()
{
    return true;
}

bool Guerrier::move(Direction dir, Carte &carte)
{
    Coordinate c = getDirCoordinate(dir);
    Position oldPos = this->_pos;
    Position newPos = Position(_pos.getPosX() + c.x, _pos.getPosY() + c.y);

    if (carte.updatePos(this, oldPos, newPos))
    {
        setPosition(newPos);
        return true;
    }

    return false;
}
