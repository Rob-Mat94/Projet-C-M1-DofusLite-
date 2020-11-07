#include "../includes/Carte.h"
#include <iostream>
#include "../includes/Obstacle.h"
#include "../includes/Guerrier.h"
#include "../includes/ObjetRamassable.h"

Carte::Carte():_width(0),_height(0),_map(){}

Carte::Carte(std::string file_name)
{   
    std::ifstream file_map("res/"+file_name,std::ios::in);
    if(file_map)
    {   
        file_map >> this->_width;
        file_map >> this ->_height;
        
        for(int i = 0; i < this->_height; i++)
            this->_map.push_back({0,0,0,0,0,0,0,0,0,0});

        file_map.ignore();
        init_map(file_map);
    }
    else
        std::cerr << "Fichier Introuvable" << std::endl;
    
    
}

void Carte :: init_map(std::ifstream &f)
{
    std::string line = "";
    int y = 0;
    while(getline(f,line)){   
        for(int i(0); i < _width ;i++){
            if(line[i] == '*')
                this->_map[y][i] = new Obstacle(Position(i,y));
            else if(line[i] =='g')
                this->_map[y][i] = new Guerrier("team 2", Position(i,y));
            else if(line[i] == 'G')
                  this->_map[y][i] = new Guerrier("team 1", Position(i,y));
            else if(line[i] == ' ')
                this->_map[y][i] = new Element(Position(i,y));
            else if(line[i] >= '0' && line[i] <= '9')
                this->_map[y][i] = new ObjetRamassable(line[i]-48, Position(i,y));
            else
                std::cerr << "Erreur dans .txt" << std::endl;
        }    
        y++;
    }
}

void Carte::printMap()const
{   
    for(const auto &tab : this->_map){
        for(const auto &element : tab){   
            std::cout << element->getDraw();
        }
        std::cout << std::endl;
    }
}

Carte::~Carte()
{   
    for(const auto &tab : this->_map){
        for(const auto &element : tab) {
            if(element != nullptr) {
                delete element;
            }
        }
    }
}

