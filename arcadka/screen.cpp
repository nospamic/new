#include "screen.h"

Screen::Screen()
{
    sizeX = 100;
    sizeY = 40;
    FastConsole f(sizeX, sizeY);
    console = f;

}

void Screen::setMap(Map &map, un posX, un posY)
{
    DynArry<char>pic(sizeX, sizeY, ' ');
    for(un y=0; y<sizeY; y++)
    {
        for(un x=0; x<sizeX; x++)
        {
            if(x+posX < map.sizeX && y+posY < map.sizeY) pic.setElement(x,y,map.space.getElement(x+posX,y+posY).symbol);
        }
    }
    console.setPicture(pic, 0, 0);

}

void Screen::setObject(ArcObject &arcobj)
{
    DynArry<char>pic(arcobj.sizeX, arcobj.sizeY, ' ');
    for(un y=0; y<arcobj.sizeY; y++)
    {
        for(un x=0; x<arcobj.sizeX; x++)
        {
            pic.setElement(x,y,arcobj.body.getElement(x,y).symbol);
        }
    }
    console.setPicture(pic, sizeX/2 - pic.sizeX/2, sizeY/2 - pic.sizeY/2);

}

void Screen::show()
{
    console.show();
}
