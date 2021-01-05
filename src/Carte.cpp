#include <iostream>
#include <algorithm>
#include <memory>

#include "../includes/Carte.h"
#include "../includes/Sword.h"
#include "../includes/Armor.h"
#include "../includes/Potion.h"
#include "../includes/EmptyElement.h"

Carte::Carte(std::string file_name, Game *game)
{
    this->_game = game;
    std::ifstream file_map("res/" + file_name, std::ios::in);
    if (file_map)
    {
        file_map >> this->_width;
        file_map >> this->_height;
        _map = std::vector<std::vector<Element *>>(_height, std::vector<Element *>(_width, 0));

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
                addElement(new Guerrier("team 1", Position(x, y)));
                _game->addGuerrier(dynamic_cast<Guerrier *>(_map[y][x]));
                break;
            case 'S':
                // sword avec 30 points d'attaques en plus pour le guerrier
                addElement(new Sword(30, Position(x, y)));
                break;
            case 'A':
                // armor avec 30 points de défence en plus pour le guerrier
                addElement(new Armor(50, Position(x, y)));
                break;
            case 'G':
                addElement(new Guerrier("team 2", Position(x, y)));
                _game->addGuerrier(dynamic_cast<Guerrier *>(_map[y][x]));
                break;
            case ' ':
                addElement(new EmptyElement(Position(x, y)));
                break;
            default:
                if (line[x] >= '0' && line[x] <= '9')
                    addElement(new Potion((line[x] - 48) * 10, Position(x, y)));
                else
                {
                    std::cerr << "Erreur dans .txt" << std::endl;
                    exit(1);
                }
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
    addElement(new EmptyElement(e->getPosition()));
    // au cas ou c'est un guerrier il sera supprimé aussi dans game !
    _game->removeGuerrier(dynamic_cast<Guerrier *>(e));
    delete e;
}

bool Carte::canMove(Position oldPos, Position newPos) const
{
    int x(newPos.getPosX()), y(newPos.getPosY()),
        x2(oldPos.getPosX()), y2(oldPos.getPosY());

    if (x >= _width || y >= _height || x2 >= _width || y2 >= _height || x < 0 || y < 0 || x2 < 0 || y2 < 0)
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
    addElement(new EmptyElement(oldPos));

    e->element_action(g);

    delete e;
    _map[y][x] = tmp;
    return true;
}

Guerrier *Carte::checkEnemy(Guerrier *g)
{
    int x = g->getPosition().getPosX(),
        y = g->getPosition().getPosY();

    if (y - 1 >= 0 && g->estAdversaire(dynamic_cast<Guerrier *>(this->_map[y - 1][x])))
        return dynamic_cast<Guerrier *>(this->_map[y - 1][x]);

    else if (x + 1 < _width && g->estAdversaire(dynamic_cast<Guerrier *>(this->_map[y][x + 1])))
        return dynamic_cast<Guerrier *>(this->_map[y][x + 1]);

    else if (y + 1 < _height && g->estAdversaire(dynamic_cast<Guerrier *>(this->_map[y + 1][x])))
        return dynamic_cast<Guerrier *>(this->_map[y + 1][x]);

    else if (x - 1 >= 0 && g->estAdversaire(dynamic_cast<Guerrier *>(this->_map[y][x - 1])))
        return dynamic_cast<Guerrier *>(this->_map[y][x - 1]);

    return nullptr;
}

std::vector<std::vector<char>> Carte::getMap() const
{
    std::vector<std::vector<char>> map = {};
    for (auto l : _map)
    {
        std::vector<char> m = {};
        for (auto e : l)
            m.push_back(e->getDraw());
        map.push_back(m);
    }
    return map;
}