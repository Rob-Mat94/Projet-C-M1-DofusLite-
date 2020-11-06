#ifndef POSITION_H
#define POSITION_H

class Position
{
    public:
        Position(const int x = 0, const int y = 0);
        virtual ~Position();
        int getPosX()const;
        int getPosY()const;
        void setPosX(const int x);
        void setPosY(const int y);

    private:
        int _x;
        int _y; 
};

#endif



