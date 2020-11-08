#include <iostream>
#include "../includes/Direction.h"

Coordinate getDirCoordinate(Direction dir)
{
    int x(0), y(0);

    switch (dir)
    {
    case Up:
        y = -1;
        break;

    case Down:
        y = 1;
        break;

    case Left:
        x = -1;
        break;

    case Right:
        x = 1;
        break;
    default:
        std::cerr << "Erreur: direction inconnu ! \n";
        exit(1);
    }

    return {x, y};
}