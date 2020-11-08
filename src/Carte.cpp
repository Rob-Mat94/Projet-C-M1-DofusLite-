#include <iostream>
#include "../includes/Carte.h"
#include "../includes/Obstacle.h"
#include "../includes/Guerrier.h"
#include "../includes/ObjetRamassable.h"


Carte::Carte() : _width(0), _height(0), _map() {}

Carte::Carte(std::string file_name)
{
    std::ifstream file_map("res/" + file_name, std::ios::in);
    if (file_map)
    {
        file_map >> this->_width;
        file_map >> this->_height;

        for (int i = 0; i < this->_height; i++)
            this->_map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

        file_map.ignore();
        init_map(file_map);
    }
    else
        std::cerr << "Fichier Introuvable" << std::endl;
}

Carte::~Carte()
{
    for (const auto &tab : this->_map)
    {
        for (const auto &element : tab)
        {
            if (element != nullptr)
            {   
                delete element;
            }
        }
    }
}

void Carte ::init_map(std::ifstream &f)
{
    std::string line = "";
    int y = 0;
    while (getline(f, line))
    {
        for (int x(0); x < _width; x++)
        {
            switch (line[x])
            {
            case '*':
                addElement(new Obstacle(Position(x, y)));
                break;
            case 'g':
                addElement(new Guerrier("team 2", Position(x, y)));
                break;
            case 'G':
                addElement(new Guerrier("team 1", Position(x, y)));
                break;
            case ' ':
                addElement(new Element(Position(x, y)));
                break;
            default:
                if (line[x] >= '0' && line[x] <= '9')
                {
                    addElement(new ObjetRamassable(line[x] - 48, Position(x, y)));
                }
                else
                {
                    std::cerr << "Erreur dans .txt" << std::endl;
                    exit(1);
                }
                break;
            }
        }
        y++;
    }
}

void Carte::printMap() const
{
    for (const auto &tab : this->_map)
    {
        for (const auto &element : tab)
        {
            std::cout << element->getDraw();
        }
        std::cout << std::endl;
    }
}

void Carte::addElement(Element *e)
{
    if (e != nullptr)
    {
        int x(e->getPosition().getPosX()),
            y(e->getPosition().getPosY());
        _map[y][x] = e;
    }
}


bool Carte::can_Move(Guerrier * g, Direction& d)
{    
    Position new_p (g->getPosition().getPosX() + getDirCoordate(d).x,g->getPosition().getPosY() + getDirCoordate(d).y);
    if(new_p.getPosX() > this->_width || new_p.getPosY() > this->_height)
        return false;
    if(this->_map[new_p.getPosY()][new_p.getPosX()]->element_action())
        return false;

    return true;
}

void Carte::moveG(Guerrier* g, Direction& d)
{   
    if(!can_Move(g,d))
        return;

    Position new_p (g->getPosition().getPosX() + getDirCoordate(d).x,g->getPosition().getPosY() + getDirCoordate(d).y);
    Position old_p = g->getPosition();
    
    Element* old = this->_map[new_p.getPosY()][new_p.getPosX()];
    old->setPosition(old_p);
    g->setPosition(new_p);

    this->_map[new_p.getPosY()][new_p.getPosX()] = g;
    this->_map[old_p.getPosY()][old_p.getPosX()] = old;
}