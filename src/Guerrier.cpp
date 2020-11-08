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
bool Guerrier::element_action()
{
    return true;
}

bool Guerrier::move(Direction dir, Carte &carte)
{
    Position oldPos = this->_pos;
    Coordinate c = getDirCoordinate(dir);

    _pos.setPosX(_pos.getPosX() + c.x);
    _pos.setPosY(_pos.getPosY() + c.y);
    Position newPos = this->_pos;

    return carte.updatePos(oldPos, newPos);
}
