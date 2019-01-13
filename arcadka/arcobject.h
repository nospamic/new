#ifndef ARCOBJECT_H
#define ARCOBJECT_H

#include <iostream>
#include <windows.h>
#include <string>
#include "dynarry.h"
#include "cell.h"

class ArcObject
{
public:
    virtual void setView() = 0;
    virtual void live() = 0;
    enum CELLTYPE {BORDER, PLAYER, BILDING, ENEMY, EMPTY};
    float posX, posY;
    un sizeX, sizeY;
    un id;
    DynArry<Cell>body;
    DynArry<Cell>view;
    Cell piece;
    //ArcObject ();
};

#endif // ARCOBJECT_H
