#include "fastconsole.h"

FastConsole::FastConsole(un sizeX, un sizeY)
{

    this->sizeX = sizeX;
    this->sizeY = sizeY;
    screen.sizeX = sizeX;
    screen.sizeY = sizeY;
    screen.fillArr(' ');
    buffer.sizeX = sizeX;
    buffer.sizeY = sizeY;
    buffer.fillArr(' ');
    prepare();
}

FastConsole::FastConsole()
{

}






void FastConsole::prepare()
{
    setlocale (LC_ALL,"Russian");
    HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD maxWindow;
    maxWindow.X = sizeX - 1;
    maxWindow.Y = sizeY - 1;
    SMALL_RECT srctWindow = { 0, 0, maxWindow.X, maxWindow.Y};
    maxWindow.X = sizeX;
    maxWindow.Y = sizeY;
    SMALL_RECT minWindow = { 0, 0, 0, 0 };
    SetConsoleWindowInfo(out_handle, true, &minWindow);
    SetConsoleScreenBufferSize(out_handle, maxWindow);
    SetConsoleWindowInfo(out_handle, true, &srctWindow);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("cls");
}

void FastConsole::setPicture(DynArry<char> pic, un Xpos, un Ypos)
{
    for (un y = 0; y < pic.sizeY; y++)
    {
        for (un x = 0; x < pic.sizeX; x++)
        {
           if(x+Xpos < sizeX && y+Ypos < sizeY && pic.getElement(x,y) != ' ') buffer.setElement(x+Xpos, y+Ypos, pic.getElement(x,y));
        }
    }
}

void FastConsole::setRectangle(un posX, un posY, un sizeX, un sizeY, char brush)
{
    DynArry<char> rec(sizeX,sizeY,' ');
    for(un n=0; n<sizeX; n++)
    {
        rec.setElement(n,0,brush);
        rec.setElement(n,sizeY-1,brush);
    }
    for(un n=1; n<sizeY-1; n++)
    {
        rec.setElement(0,n,brush);
        rec.setElement(sizeX-1,n,brush);

    }
    setPicture(rec,posX,posY);
}


void FastConsole::setCircle(un posX, un posY, un radius, char brush)
{
    if (radius !=0)
    {
        DynArry<char> circle(radius*2+1,radius*2+1,' ');
        circle.setCircle(0, 0, radius, brush);
        setPicture(circle, posX, posY);
    }
}


void FastConsole::setLine(un posX, un posY, int sizeX, int sizeY, char brush)
{



    int antinullX=1;
    int antinullY=1;
    //sizeX==0?antinullX=1:antinullX=0;
    //sizeY==0?antinullY=1:antinullX=0;
    DynArry<char>line(abs(sizeX)+antinullX, abs(sizeY)+antinullY, '.');

    int x, y;
    int xArr, yArr;
    sizeX<0 ? x=posX-abs(sizeX)+1 : x=posX;
    sizeY<0 ? y=posY-abs(sizeY)+1 : y=posY;
    sizeX<0 ? xArr=abs(sizeX) : xArr=0;
    sizeY<0 ? yArr=abs(sizeY) : yArr=0;


    line.setLine(xArr,yArr,sizeX,sizeY,brush);
    setPicture(line,x,y);
}


void FastConsole::show()
{
    for (un y = 0; y < sizeY; y++)
    {
        for (un x = 0; x < sizeX; x++)
        {
            if (screen.getElement(x,y) != buffer.getElement(x,y))
            {
                screen.setElement(x, y, buffer.getElement(x,y));
                setCursor(x, y);
//                std::cout<<"getElement(x,y)-"<<buffer.getElement(x,y)<<"\n";
//                system("pause");
                if(!(x==sizeX-1 && y==sizeY-1))std::cout << buffer.getElement(x,y);

                //Sleep (10);
            }
        }
    }
    setCursor(0,0);
    reset();
}

void FastConsole::resetScr()
{
    for (un y = 0; y < sizeY; y++)
    {
        for (un x = 0; x < sizeX; x++)
        {
            buffer.setElement(x, y, ' ');
            if (screen.getElement(x,y) != ' ')
            {
                screen.setElement(x, y, ' ');
                setCursor(x, y);
                std::cout << ' ';
            }
        }
    }
}

void FastConsole::reset()
{
    buffer.fillArr(' ');
}


void FastConsole::setCursor(un x, un y)
{
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
