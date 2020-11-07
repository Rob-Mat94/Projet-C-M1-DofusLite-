#ifndef OBJECT_RAMASSABLE_H
#define OBJECT_RAMASSABLE_H
#include "../includes/Element.h"

class ObjetRamassable : public Element
{
    public:
        ObjetRamassable(const int hp,Position pos = Position(0,0));
        virtual ~ObjetRamassable();
        void element_action();

        const int getHpToGive()const{return _hp_to_give;}

         /* Représentation (caractère pour l'instant) */
         char getDraw(){return _hp_to_give+'0';}
    private:
        const int _hp_to_give;
};

#endif 