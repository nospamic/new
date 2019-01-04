#ifndef ARCOBJECT_H
#define ARCOBJECT_H

#include <iostream>
#include <Windows.h>
#include <string>
#include "dynarry.h"
#include "cell.h"

class ArcObject
{
public:

    enum CELLTYPE {BORDER, PLAYER, BILDING, ENEMY, EMPTY};
    double posX, posY;
    un sizeX, sizeY;
    DynArry<Cell>body;
    DynArry<Cell>view;
    Cell piece;
    ArcObject ();
};

#endif // ARCOBJECT_H
