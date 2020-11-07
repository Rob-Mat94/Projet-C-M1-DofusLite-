#ifndef CARTE_H
#define CARTE_H

#include "Element.h"
#include <vector>
#include <fstream>
#include <memory>

class Carte
{
    public:
        Carte();
        Carte(std::string file_name);
        virtual ~Carte();

        const int getWidth()const{return this->_width;}
        const int getHeight()const{return this->_height;}

        void printMap()const;
       
    private:
        void init_map(std::ifstream& f);

        int _width;
        int _height; 
        std::vector<std::vector<Element*>> _map ;

};







#endif