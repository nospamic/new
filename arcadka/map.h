#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <Windows.h>
#include <string>
#include "dynarry.h"
#include "cell.h"


class Map
{
public:
    Map();
    Map(un gameSizeX, un gameSizeY);

    DynArry<Cell>space;
    DynArry<Cell>view;
    un sizeX;
    un sizeY;
    un gameSizeX;
    un gameSizeY;
    un startX;
    un startY;

    void clear();
    void setObject(DynArry<Cell> arr, un xPos, un yPos);

private:
    un padding;
    un borderWidth;
    Cell border;
    Cell empty;
};

#endif // MAP_H
