#ifndef POSITION_H
#define POSITION_H

class Position
{
public:

    bool operator==(const Position &p)const;
    Position(const int x = 0, const int y = 0);
    Position(const Position &pos);
    virtual ~Position();
    int getPosX() const;
    int getPosY() const;
    void setPosX(const int x);
    void setPosY(const int y);

private:
    int _x;
    int _y;
};

#endif
