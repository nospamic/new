#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <Windows.h>
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
    void feel(DynArry<Cell>space);
    void move(DynArry<Cell>space);
    void control();
private:
    void setView();


};

#endif // PLAYER_H
