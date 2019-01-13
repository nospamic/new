#ifndef ARCMOB_H
#define ARCMOB_H
#include "arcobject.h"


class ArcMob : public ArcObject
{
public:
    ArcMob();
    void setView() override;
    void live() override;
    float angle;
    float speedX, speedY;
    bool blockF, blockB;
    int hp;

protected:

};



#endif // ARCMOB_H
