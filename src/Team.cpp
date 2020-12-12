#include "../includes/Team.h"

void Team::addGuerrier(Guerrier *g)
{
    _list.push_back(g);
}

void Team::removeGuerrier(Guerrier *g)
{
    _list.remove(g);
}

Guerrier *Team::getCurrent()
{
    current = current % _list.size();
    if (_list.empty())
        return nullptr;
    auto it = _list.begin();
    std::advance(it, current);
    return *it;
}

void Team::increment()
{
    current++;
    this->current = current % _list.size();
}