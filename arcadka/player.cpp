#include "player.h"



Player::Player(un posX, un posY, un sizeX, un sizeY, int hp)
{
    this->posX = posX;
    this->posY = posY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->hp = hp;
    this->piece.symbol = ' ';
    this->piece.type = Cell::EMPTY;
    DynArry<Cell> d(sizeX, sizeY, piece);
    this->body = d;
    this->speedX = 0;
    this->speedY = 0;
    this->angle = 0;

//        for(un x=0; x<this->sizeX;x++)
//        {
//            Cell cell;
//            cell.type = Cell::PLAYER;
//            cell.symbol = char(int(x)+48);
//            body.setElement(x,0,cell);
//        }
        Cell cell;
        cell.type = Cell::PLAYER;
        cell.symbol = '#';
        body.setRectangle(3,3,sizeX-6,sizeY-6,cell,piece);
        cell.symbol = '0';
        body.setElement(4,2,cell);
        body.setElement(sizeX-5,2,cell);



    view = body;

}

Player::Player()
{

}

void Player::feel(DynArry<Cell> space)
{

    if(speedY < 0)
    {
    for(un x=posX; x<posX+sizeX; x++)
        {
            un y = posY - 1;
            un type = space.getElement(x,y).type;
            if(type == BORDER) speedY = 0;
        }
    }
    if(speedY > 0)
    {
    for(un x=posX; x<posX+sizeX; x++)
        {
            un y = posY + sizeY;
            un type = space.getElement(x,y).type;
            if(type == BORDER) speedY = 0;
        }
    }
}

void Player::move(DynArry<Cell> space)
{
    control();
    setView();
    feel(space);

    if (speedY != 0)
    {
        double alpha = (angle+90) * 3.1415 / 180;
        posX += cos(alpha) * double(speedY);
        posY += sin(alpha) * double(speedY);
    }
}

void Player::control()
{
    GetKeyState(VK_RIGHT)&0x80 ? angle+=2 : GetKeyState(VK_LEFT)&0x80 ? angle-=2 : true;
    GetKeyState(VK_DOWN )&0x80 ? speedY = 1 : GetKeyState(VK_UP  )&0x80 ? speedY = -1 : speedY = 0;
}

void Player::setView()
{
    view = body;
    view.rotate(int(sizeX/2),int(sizeY/2),angle);
}
