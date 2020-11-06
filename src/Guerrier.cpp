#include "../includes/Guerrier.h"

Guerrier::Guerrier(const std::string team,Position pos,int hp, std::string name, int capAttack, int capDef)
:Element(pos),_hp(hp),_name(name),_team(team),_capAttack(capAttack),_capDef(capDef){}

Guerrier::~Guerrier(){}

void Guerrier:: element_action()
{
    /* TO DO */
}

