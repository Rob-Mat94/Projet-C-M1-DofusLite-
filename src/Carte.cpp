#include <iostream>
#include <algorithm>
#include <memory>

#include "../includes/Carte.h"
#include "../includes/Sword.h"
#include "../includes/Armor.h"
#include "../includes/Potion.h"

std::vector<Guerrier *> Carte::_team_1{};
std::vector<Guerrier *> Carte::_team_2{};

Carte::Carte() : _width(0), _height(0), _map() {}

Carte::Carte(std::string file_name)
{
    std::ifstream file_map("res/" + file_name, std::ios::in);
    if (file_map)
    {
        file_map >> this->_width;
        file_map >> this->_height;

        std::vector<Element *> temp_vec;
        for (int i = 0; i < _width; i++)
            temp_vec.push_back(0);
        for (int i = 0; i < this->_height; i++)
            this->_map.push_back(temp_vec);

        file_map.ignore();
        init_map(file_map);
    }
    else
    {
        std::cerr << "Fichier Introuvable" << std::endl;
        exit(1);
    }
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
                _team_2.push_back(dynamic_cast<Guerrier *>(_map[y][x]));
                break;
            case 'S':
                addElement(new Sword(15, Position(x, y)));
                break;
            case 'A':
                addElement(new Armor(20, Position(x, y)));
                break;
            case 'G':
                addElement(new Guerrier("team 1", Position(x, y)));
                _team_1.push_back(dynamic_cast<Guerrier *>(_map[y][x]));
                break;
            case ' ':
                addElement(new Element(Position(x, y)));
                break;
            default:
                if (line[x] >= '0' && line[x] <= '9')
                    addElement(new Potion(line[x] - 48, Position(x, y)));
                else
                    std::cerr << "Erreur dans .txt" << std::endl;
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
            std::cout << element->getDraw() << " ";
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

void Carte::removeElement(Element *e)
{
    int x(e->getPosition().getPosX()),
        y(e->getPosition().getPosY());
    Element *tmp = _map[y][x];
    addElement(new Element(e->getPosition()));
    for (auto it = _team_1.begin(); it < _team_1.end(); it++)
        if ((*it)->getPosition() == e->getPosition())
            _team_1.erase(it);
    for (auto it = _team_2.begin(); it < _team_2.end(); it++)
        if ((*it)->getPosition() == e->getPosition())
            _team_2.erase(it);
    std::cout << "\nteam1: " << _team_1.size() << "\nteam2: " << _team_2.size() << "\n";
    delete tmp;
}

bool Carte::canMove(Position oldPos, Position newPos)
{
    int x(newPos.getPosX()), y(newPos.getPosY()),
        x2(oldPos.getPosX()), y2(oldPos.getPosY());

    if (x >= _width || y >= _height || x2 >= _width || y2 >= _height)
        return false;

    return _map[y][x]->isEmpty();
}

bool Carte::updatePos(Guerrier *g, Position oldPos, Position newPos)
{
    if (!canMove(oldPos, newPos))
        return false;

    int x(newPos.getPosX()), y(newPos.getPosY()), x2(oldPos.getPosX()), y2(oldPos.getPosY());

    Element *tmp = _map[y2][x2];
    Element *e = _map[y][x];
    addElement(new Element(oldPos));

    e->pickUpElement(g);

    delete e;
    _map[y][x] = tmp;
    return true;
}

Guerrier *Carte::CheckEnemy(Guerrier *g)
{
    int x(g->getPosition().getPosX()), y(g->getPosition().getPosY());

    if (this->_map[y - 1][x]->element_action() && g->estAdversaire(dynamic_cast<Guerrier *>(this->_map[y - 1][x])))
        return dynamic_cast<Guerrier *>(this->_map[y - 1][x]);
    else if (this->_map[y][x + 1]->element_action() && g->estAdversaire(dynamic_cast<Guerrier *>(this->_map[y][x + 1])))
        return dynamic_cast<Guerrier *>(this->_map[y][x + 1]);
    else if (this->_map[y + 1][x]->element_action() && g->estAdversaire(dynamic_cast<Guerrier *>(this->_map[y + 1][x])))
        return dynamic_cast<Guerrier *>(this->_map[y + 1][x]);
    else if (this->_map[y][x - 1]->element_action() && g->estAdversaire(dynamic_cast<Guerrier *>(this->_map[y][x - 1])))
        return dynamic_cast<Guerrier *>(this->_map[y][x - 1]);

    return nullptr;
}
