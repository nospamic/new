#include "food.h"


void Food::setView()
{

}

void Food::live()
{

}

Food::Food(un posX, un posY, un sizeX, un sizeY, un id)
{
    dead = false;
    this->posX = posX;
    this->posY = posY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->id = id;
    Cell cell(Cell::ENEMY, char(176), id);
    Cell empty(Cell::EMPTY, ' ', id);
    body = DynArry<Cell>(sizeX,sizeY,empty);
    body.setCircle(0, 0, sizeX/2, cell);
    view = body;
}

void Food::death()
{
    dead = true;
    sizeX--;
    sizeY--;
    view.fillArr();
    Cell cell(Cell::ENEMY, char(176), id);
    view.setCircle(0, 0, sizeX/2, cell);
}
