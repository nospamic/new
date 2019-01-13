#ifndef SCREEN_H
#define SCREEN_H

#include <windows.h>
#include "map.h"
#include "fastconsole.h"
#include "dynarry.h"
#include "arcobject.h"
#include "arcmob.h"
#include "player.h"

class Screen
{
public:
    Screen();

    un sizeX, sizeY;
    void setMap(Map &map, un posX, un posY);
    void setObject(ArcObject &arcobj);
    void show();
private:
    FastConsole console;

};

#endif // SCREEN_H
