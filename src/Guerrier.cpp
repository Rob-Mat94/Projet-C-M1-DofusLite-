#include "../includes/Guerrier.h"

std::vector<std::string> Guerrier::_name_list = {"Gareth", "Lancelot", "Arthur", "Perceval", "Leodagan", "Yvain", "Robert", "Sagremor"};
int Guerrier::_name_list_index = rand() % _name_list.size();

Guerrier::Guerrier(const std::string team, Position pos, int hp, std::string name, int capAttack, int capDef)
    : Element(pos), _hp(hp), _name(_name_list[_name_list_index]), _team(team), _capAttack(capAttack), _capDef(capDef)
{
    _name_list_index = rand() % _name_list.size();
}

bool Guerrier::estAdversaire(Guerrier *g)
{
    if (g == nullptr)
        return false;

    if (g->getTeam() == this->_team)
        return false;
    return true;
}

char Guerrier::getDraw() const
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

bool Guerrier::element_action(Element *e)
{
    return false;
}

bool Guerrier::move(Direction dir, Carte *carte)
{
    Coordinate c = getDirCoordinate(dir);
    Position oldPos = this->_pos;
    Position newPos = Position(_pos.getPosX() + c._x, _pos.getPosY() + c._y);

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