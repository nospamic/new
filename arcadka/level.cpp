#include "level.h"

Level::Level()
{    
    map = Map (200,200);
    player = Player (map.startX, map.startY, 9, 9, 100);
    Food border(map.padding, map.padding ,map.getBorder().sizeX, map.getBorder().sizeY,0);
    border.view = map.getBorder();
    food.push_back(border);
    FoodCreate();
    setArea();

}

void Level::play()
{
    do
    {
        move();
    }
    while(true);
}


void Level::FoodCreate()
{
    un id = 1;
    for(un y=map.padding+3; y<map.sizeY-map.padding-3;y+=30)
    {
        for(un x=map.padding+3; x<map.sizeX-map.padding-3;x+=40)
        {
            Food f(x,y,7,7, id);
            food.push_back(f);
            id++;
        }
    }
}

void Level::setFood()
{
    for (auto f : food)setObjToMap(&(f));
}

void Level::setArea()
{
    un margin = screen.sizeX/2;
    area.x = int(player.posX) - int(screen.sizeX/2 - player.sizeX/2)-margin;
    area.y = int(player.posY)- int(screen.sizeY/2 - player.sizeY/2)-margin;
    area.x<0?area.x=0:true;
    area.y<0?area.y=0:true;
    area.w = screen.sizeX+margin*2;
    area.h = screen.sizeY+margin*2;
}


void Level::setObjToMap(ArcObject *obj)
{
    map.setObject(obj->view,unsigned(obj->posX),unsigned(obj->posY), area);
}



void Level::move()
{
    bool rotate = 0;
    if(true)
    {
        setArea();
        setFood();
        player.live();

        feel();

        setObjToMap(&player);


        if(rotate)
        {
            Map mapTurned = map;
            mapTurned.space.rotate(player.posX + player.sizeX/2, player.posY + player.sizeY/2, player.angle*(-1)  );
            screen.setMap(mapTurned, player.posX - (screen.sizeX/2 - player.sizeX/2) , player.posY- (screen.sizeY/2 - player.sizeY/2));
        }
        else
        {
            screen.setMap(map, player.posX - (screen.sizeX/2 - player.sizeX/2) , player.posY- (screen.sizeY/2 - player.sizeY/2));
        }
        screen.show();
        //std::cout <<area.x<<" "<<area.w;// food.size()-1<<" ";//player.angle<<" posX:"<<feelFront().id<<" [1]"<<food[1].id;

        Sleep(10);
        map.clear(area);

    }
}

Cell Level::feelFront()
{
    Cell res(Cell::EMPTY,' ',0);
    for(un y=0;y<player.sizeY;y++)
    {
        for(un x=0;x<player.sizeX;x++)
        {
            if(player.view.get(x,y).type == Cell::SENSOR_F
            && map.space.get(x+unsigned(player.posX), y+unsigned(player.posY)).type != Cell::EMPTY)
            {return map.space.get(x+unsigned(player.posX), y+unsigned(player.posY));}
        }
    }

  return res;
}

Cell Level::feelBack()
{
    Cell res(Cell::EMPTY,' ',0);
    for(un y=0;y<player.sizeY;y++)
    {
        for(un x=0;x<player.sizeX;x++)
        {
            if(player.view.get(x,y).type == Cell::SENSOR_B
            && map.space.get(x+unsigned(player.posX), y+unsigned(player.posY)).type != Cell::EMPTY)
            {return map.space.get(x+unsigned(player.posX), y+unsigned(player.posY));}
        }
    }

    return res;
}

void Level::feel()
{
    Cell front = feelFront();
    Cell back  = feelBack();
    if(front.type != Cell::EMPTY && front.type != Cell::DECOR)
    {
        player.blockF = true;
        for(un n=0;n<food.size();n++)
        {
            if(front.type == Cell::ENEMY && front.id == food[n].id)
            {
                food[n].death();
                if (food[n].sizeX==0 && food[n].dead)
                {
                    food.erase(food.begin() + int(n));
                    player.sizeX++;
                    player.sizeY++;
                    player.refresh();
                }
                break;
            }
        }
    }
    else
    {
        player.blockF = false;
    }
    if(back.type != Cell::EMPTY && back.type != Cell::DECOR){player.blockB = true;}else{player.blockB = false;}

}
