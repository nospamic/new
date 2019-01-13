#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <windows.h>
#include <string>
#include "dynarry.h"
#include "arcmob.h"
#include "map.h"
#include "cell.h"


class Player : public ArcMob
{
public:
    Player(un posX, un posY, un sizeX, un sizeY, int hp);
    Player();

    void move();
    void live()override;
    void control();
    void refresh();
private:



};

#endif // PLAYER_H
