#include "map.h"

Map::Map()
{

}

Map::Map(un gameSizeX, un gameSizeY)
{
    borderWidth = 3;
    gameSizeX > gameSizeY ? padding = gameSizeX/2 : padding = gameSizeY/2;
    this->gameSizeX = gameSizeX;
    this->gameSizeY = gameSizeY;
    sizeX = gameSizeX + (padding * 2) + (borderWidth * 2);
    sizeY = gameSizeY + (padding * 2) + (borderWidth * 2);
    empty = Cell(Cell::EMPTY, ' ', 0);
    border = Cell(Cell::BORDER, char(177) , 0);
    space = DynArry<Cell>(sizeX, sizeY, empty);
    startX = sizeX/2;
    startY = sizeY/2;
}


DynArry<Cell> Map::getBorder()
{
    DynArry<Cell>borderLine(gameSizeX+borderWidth*2, gameSizeX+borderWidth*2, empty);
    for(un n=0;n<borderWidth;n++)
    {
        borderLine.setRectangle(n, n, gameSizeX+(borderWidth*2)-(n*2), gameSizeY+(borderWidth*2)-(n*2),border,empty);
    }

    Cell point(Cell::DECOR,'.',0);
    for(un y=borderWidth; y<gameSizeY;y+=10)
    {
        for(un x=borderWidth; x<gameSizeX;x+=14)
        {
            borderLine.set(x,y,point);
        }
    }

    return borderLine;
}


void Map::clear(Area area)
{

    for(un y=area.y; y<area.y+area.h;y++)
    {
        for(un x=area.x; x<area.x+area.w;x++)
        {
            if (space.get(x,y).type!=Cell::BORDER && space.get(x,y).type != Cell::EMPTY)
                space.set(x,y,empty);
        }
    }
}


void Map::setObject(DynArry<Cell> &arr, un xPos, un yPos, Area area)
{
    un xStart;
    un xEnd;
    un yStart;
    un yEnd;
    (area.x<xPos) ?  xStart=xPos :  xStart = area.x;
    (area.x+area.w > xPos+arr.sizeX) ? xEnd=xPos+arr.sizeX : xEnd=area.x+area.w;
    (area.y<yPos) ?  yStart=yPos :  yStart = area.y;
    (area.y+area.h > yPos+arr.sizeY) ? yEnd=yPos+arr.sizeY : yEnd=area.y+area.h;

    for(un y=yStart;y<yEnd;y++)
    {
        for(un x=xStart; x<xEnd;x++)
        {
            un type = arr.get(x-xPos,y-yPos).type;
            if(type !=Cell::EMPTY && type != Cell::SENSOR_F && type != Cell::SENSOR_B ) space.set(x,y,arr.get(x-xPos,y-yPos));
        }
    }
}


