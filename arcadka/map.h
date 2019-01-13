#ifndef MAP_H
#define MAP_H

#include <iostream>
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
    un padding;
    un borderWidth;
    //void setBorder();
    DynArry<Cell> getBorder();
    void clear(Area area);
    void setObject(DynArry<Cell> &arr, un xPos, un yPos, Area area);

private:


    Cell border;
    Cell empty;
};

#endif // MAP_H
