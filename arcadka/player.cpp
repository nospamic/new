#include "player.h"



Player::Player(un posX, un posY, un sizeX, un sizeY, int hp)
{
    this->posX = posX;
    this->posY = posY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->hp = hp;
    this->speedX = 0;
    this->speedY = 0;
    this->angle = 0;
    blockF = false;
    blockB = false;
    piece = Cell(Cell::EMPTY, ' ', 0);
    refresh();

}

Player::Player()
{

}

void Player::refresh()
{
    body = DynArry<Cell> (sizeX, sizeY, piece);
    Cell cell = Cell(Cell::PLAYER,'#',0);
    body.setRectangle(3,3,sizeX-6,sizeY-6,cell,piece);
    cell.symbol = '0';
    body.set(4,2,cell);
    body.set(sizeX-5,2,cell);
    Cell sensorF(Cell::SENSOR_F,'.',0);
    Cell sensorB(Cell::SENSOR_B,'.',0);
    for(un x=3;x<sizeX-3;x++)
    {
        body.set(x,1,sensorF);
        body.set(x,sizeY-2,sensorB);
    }
    setView();
}


void Player::move()
{
    if (int(speedY) != 0)
    {
        blockF?speedY=1:true;
        blockB?speedY=-1:true;
        float alpha = (angle+90) * 3.1415 / 180;
        posX += cos(alpha) * float(speedY);
        posY += sin(alpha) * float(speedY);
    }
}

void Player::live()
{
    control();
    setView();
    move();
}


void Player::control()
{
    if(GetKeyState(VK_RIGHT)&0x80){ angle+=3;}
    if(GetKeyState(VK_LEFT)&0x80) {angle-=3;}
    if(GetKeyState(VK_DOWN)&0x80 && !blockB) {speedY = 1;}
    else if(GetKeyState(VK_UP)&0x80 && !blockF){speedY = -1;}
    else {speedY = 0;}

}




