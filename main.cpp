#include <iostream>
#include <vector>
#include "includes/Guerrier.h"
#include "includes/Obstacle.h"
#include "includes/Position.h"
#include "includes/ObjetRamassable.h"


int main()
{      
    ObjetRamassable o {100};
    Obstacle ob{Position(150,180)};
   // std::cout << " x : " << ob.getPosition().getPosX() << " / y : " << ob.getPosition().getPosY();
    std::vector<Element*> tab;  
    tab.push_back(new Obstacle(Position(12,12)));
    tab.push_back(new ObjetRamassable(50,Position(45,452)));

    for(int i = 0; i < tab.size(); i++)
    {
        std::cout << tab[i]->getPosition().getPosX() << " / " << tab[i]->getPosition().getPosY() << std::endl; 
        delete tab[i];
    }

    return 0;
}