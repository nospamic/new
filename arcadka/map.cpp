#include "map.h"

Map::Map()
{

}

Map::Map(un gameSizeX, un gameSizeY)
{
    borderWidth = 1;
    gameSizeX > gameSizeY ? padding = gameSizeX/2 : padding = gameSizeY/2;
    this->gameSizeX = gameSizeX;
    this->gameSizeY = gameSizeY;
    sizeX = gameSizeX + (padding * 2) + (borderWidth * 2);
    sizeY = gameSizeY + (padding * 2) + (borderWidth * 2);
    border.symbol = '#';
    border.type = 0;
    empty.symbol = ' ';
    empty.type = 4;
    DynArry<Cell>sp(sizeX, sizeY, empty);
    space = sp;
    space.setRectangle(padding+borderWidth, padding+borderWidth, gameSizeX+(borderWidth*2), gameSizeY+(borderWidth*2),border,empty);
    startX = sizeX/2;
    startY = sizeY/2;
    Cell cell;
    cell.type = Cell::EMPTY;
    cell.symbol = '*';
    for(un y=padding+3; y<sizeY-padding-3;y+=20)
    {
        for(un x=padding+3; x<sizeX-padding-3;x+=30)
        {
            space.setCircle(x,y,3,cell);
        }
    }

}


void Map::clear()
{
    for(un y=0; y<space.sizeY;y++)
    {
        for(un x=0; x<space.sizeX;x++)
        {
            if (space.getElement(x,y).type!=Cell::BORDER && space.getElement(x,y).type != Cell::EMPTY)
                space.setElement(x,y,empty);
        }
    }
}


void Map::setObject(DynArry<Cell> arr, un xPos, un yPos)
{
    for(un y=yPos;y<yPos+arr.sizeY;y++)
    {
        for(un x=xPos; x<xPos+arr.sizeX;x++) space.setElement(x,y,arr.getElement(x-xPos,y-yPos));
    }
}


