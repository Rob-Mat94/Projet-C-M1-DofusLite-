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
    _current = _current % _list.size();
    if (_list.empty())
        return nullptr;
    auto it = _list.begin();
    std::advance(it, _current);
    return *it;
}

void Team::increment()
{
    _current++;
    this->_current = _current % _list.size();
}