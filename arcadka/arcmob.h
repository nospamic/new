#ifndef ARCMOB_H
#define ARCMOB_H
#include "arcobject.h"


class ArcMob : public ArcObject
{
public:
    ArcMob();

    double angle;
    float speedX, speedY;
    int hp;

protected:

};

#endif // ARCMOB_H
