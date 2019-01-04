#include "level.h"

Level::Level()
{    
    Map m(100,100);
    map = m;
    Player p(map.startX, map.startY, 16, 16, 100);
    this->player = p;
}

void Level::play()
{
    do
    {
        move();
    }
    while(true);
}

void Level::setObjToMap(ArcObject *obj, Map &map)
{
    map.setObject(obj->view,unsigned(obj->posX),unsigned(obj->posY));
}


void Level::shadow()
{
    Cell shad;
    shad.type = Cell::EMPTY;
    shad.symbol = '.';
    map.space.setRectangle(unsigned(player.posX), unsigned(player.posY), player.sizeX, player.sizeY, shad, shad);
}






void Level::move()
{
    if(true)
    {
        player.move(map.space);

        setObjToMap(&player, map);
        //Map mapTurned = map;
        //mapTurned.space.rotate(player.posX + player.sizeX/2, player.posX + player.sizeX/2, player.angle*(-1)  );
        screen.setMap(map, player.posX - (screen.sizeX/2 - player.sizeX/2) , player.posY- (screen.sizeY/2 - player.sizeY/2));
        //screen.setObject(this->player);
        screen.show();
        map.clear();
        Sleep(20);
        std::cout << player.angle<<" posX:"<<player.posX;
    }
}
