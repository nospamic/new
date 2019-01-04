#ifndef LEVEL_H
#define LEVEL_H

#include <conio.h>
#include "fastconsole.h"
#include "dynarry.h"
#include "screen.h"
#include "map.h"
#include "player.h"


class Level
{
public:
    Level();
    void play();
    void setObjToMap(ArcObject *obj, Map &map);
private:

    Screen screen;
    Map map;
    Player player;

    void shadow();
    void move();
};

#endif // LEVEL_H
