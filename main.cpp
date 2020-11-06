#include <iostream>

#include "includes/Guerrier.h"
#include "includes/Obstacle.h"
#include "includes/Position.h"
#include "includes/ObjetRamassable.h"


int main()
{      
    ObjetRamassable o {100};
    Obstacle ob{Position(150,180)};
    std::cout << " x : " << ob.getPosition().getPosX() << " / y : " << ob.getPosition().getPosY();  
    
    return 0;
}