#ifndef LEVEL_H
#define LEVEL_H

#include <conio.h>
#include "fastconsole.h"
#include "dynarry.h"
#include "screen.h"
#include "map.h"
#include "player.h"
#include "food.h"


class Level
{
public:
    Level();
    void play();
    void setObjToMap(ArcObject *obj);
private:
    std::vector<Food>food;
    void FoodCreate();
    void setFood();
    Area area;
    void setArea();

    Screen screen;
    Map map;
    Player player;



    void move();
    Cell feelFront();
    Cell feelBack();
    void feel();
};

#endif // LEVEL_H
