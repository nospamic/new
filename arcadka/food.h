#ifndef FOOD_H
#define FOOD_H

#include "arcobject.h"

class Food : public ArcObject
{
public:
    void setView() override;
    void live() override;
    Food(un posX, un posY, un sizeX, un sizeY, un id);
    bool dead;
    void death();
};

#endif // FOOD_H
