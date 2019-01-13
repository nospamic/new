#include "arcmob.h"

ArcMob::ArcMob()
{

}

void ArcMob::setView()
{
    view = body;
    view.rotate(int(sizeX/2),int(sizeY/2),angle);
}

void ArcMob::live()
{

}




