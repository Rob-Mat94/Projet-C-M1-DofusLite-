#include "includes/Guerrier.h"
#include "includes/Obstacle.h"
#include "includes/Position.h"
#include "includes/ObjetRamassable.h"
#include "includes/Carte.h"

int main()
{
    Carte c{"carte1.txt"};
    c.printMap();
    return 0;
}