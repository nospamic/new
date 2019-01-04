#ifndef DYNARRY_H
#define DYNARRY_H

#include <vector>
#include <iostream>
#include <QDebug>
#include <math.h>
typedef unsigned int un;
const double PI=3.1415;


template <typename T>
class DynArry
{
public:
    DynArry(un sizeX, un sizeY, T fill);
    DynArry();
    T getElement(un xPos, un yPos);
    void setElement(un xPos, un yPos, T);
    void fillArr();
    void fillArr(T val);
    void rotate(int centerX, int centerY, double alpha);
    int rotateX(double x, double y, int centerX, int centerY, double fi);
    int rotateY(double x, double y, int centerX, int centerY, double fi);
    void setCircle(un posX, un posY, un radius, T brush);
    void setLine(un posX, un posY, int sizeX, int sizeY, T brush);
    void setRectangle(un posX, un posY, un sizeX, un sizeY, T brush, T fill);
    un sizeX, sizeY;

private:
    T fill;
    std::vector<T>base;

    //Rotate/////////////////////////////////////////////////////////////
    int round(double a);
    double angle(int x, int y, int centerX, int centerY);
    double radius(double x, double y, int centerX, int centerY);

    //------------------------------------------------------------------
};


template <typename T>
DynArry<T>::DynArry(un sizeX, un sizeY, T fill)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->fill = fill;
    this->fillArr();
}

template <typename T>
DynArry<T>::DynArry()
{
    this->sizeX = 0;
    this->sizeY = 0;
}

template <typename T>
 void DynArry<T>::fillArr()
{
    base.resize(sizeX * sizeY);
    int insertPosition = 0;
    for (un y = 0; y < sizeY; y++)
    {
        for (un x = 0; x < sizeX; x++)
        {
            base[insertPosition] = fill;
            insertPosition++;
        }
    }
}


template <typename T>
void DynArry<T>::fillArr(T val)
{
     base.resize(sizeX * sizeY);
     int insertPosition = 0;
     for (un y = 0; y < sizeY; y++)
     {
         for (un x = 0; x < sizeX; x++)
         {
             base[insertPosition] = val;
             insertPosition++;
         }
     }
}


template <typename T>
T DynArry<T>::getElement(un xPos, un yPos)
{
    return base[sizeX*yPos + xPos];
}


template <typename T>
void DynArry<T>::setElement(un xPos, un yPos, T value)
{
    if(sizeX*yPos + xPos < base.size())base[sizeX*yPos + xPos] = value;
}

template<typename T>
void DynArry<T>::setCircle(un posX, un posY, un radius, T brush)
{
    int xStart = posX+radius;
    int yStart = posY;
    setElement(xStart,yStart,brush);
    for(un n=0; n<360;n++)
    {
        un x = rotateX(xStart, yStart, posX+radius, posY+radius, n);
        un y = rotateY(xStart, yStart, posX+radius, posY+radius, n);
        if(x>=0 && x<sizeX && y>=0 && y<sizeY)setElement(x,y,brush);
    }
}



template<typename T>
void DynArry<T>::setLine(un posX, un posY, int sizeX, int sizeY, T brush)
{
    float x=posX;
    float y=posY;
    float dx, dy;

    int length = int(radius(double(sizeX), double(sizeY), 0,0));//int(x), int(y)));

    dx = float(sizeX)/float(length);
    dy = float(sizeY)/float(length);
    for(int n = 0; n<length; n++)
    {
        //std::cout<<"n="<<n<<" x="<<x<<" y="<<y<<"\n";
        if(x>=0 && round(x)<int(this->sizeX) && y>=0 && round(y)<int(this->sizeY))
        setElement(round(x),round(y),brush);
        x+=dx;
        y+=dy;
    }
}


template<typename T>
void DynArry<T>::setRectangle(un posX, un posY, un sizeX, un sizeY, T brush, T fill)
{
    for(un y=posY; y<posY+sizeY; y++)\
    {
        for(un x=posX; x<posX+sizeX; x++)
        {
            if(x>posX && x<posX+sizeX-1 && y>posY && y<posY+sizeY-1)
            {setElement(x,y,fill);}
            else
            {setElement(x,y,brush);}
        }
    }
}



template<typename T>
void DynArry<T>::rotate(int centerX, int centerY, double alpha)
{
    std::vector <T> temp(sizeX*sizeY);
    for(un n=0;n<temp.size();n++) temp[n]=fill;
//    for(un y=0; y<sizeY; y++)
//    {
//        for (un x=0; x<sizeX; x++){temp.push_back(fill);}
//    }

    for(un y=0;y<sizeY;y++)
    {
        for(un x=0;x<sizeX;x++)
        {
            int x1=rotateX(double(x),double(y), centerX, centerY, alpha);
            int y1=rotateY(double(x),double(y), centerX, centerY, alpha);
            if (x1<sizeX && y1<sizeY && x1>=0 && y1>=0){temp[x1+sizeX*y1]=base[x+sizeX*y];}
            //std::cout<<x<<"    "<<x1<<"\n";
        }
    }

    for(un y=0; y<sizeY; y++)
    {
        for (un x=0; x<sizeX; x++){base[x+sizeX*y]=temp[x+sizeX*y];}
    }
}



template<typename T>
int DynArry<T>::round(double a)
{
    if(a>=0) a-int(a)>0.5 ? a=int(a+1) : a=int(a);
    if(a<0) a-int(a)<-0.5 ? a=int(a-1) : a=int(a);
    return int(a);
}

template<typename T>
double DynArry<T>::angle(int x, int y, int centerX, int centerY)
{
    double dx=x-centerX;double dy=y-centerY;
    double alpha = ((atan(dx/dy))/PI*180);
    if (dx<0&&dy<0){alpha=360-alpha;}
    if (dx<0&&dy>=0){alpha=180-alpha;}
    if (dx>=0&&dy>0){alpha=180-alpha;}
    if (dx>0&&dy<0){alpha=0-alpha;}
    if(dy==0&&dx>0){alpha=90;}
    if(dy==0&&dx<0){alpha=270;}
    if(dy==0&&dx==0){alpha=0;}
    return alpha;
}

template<typename T>
double DynArry<T>::radius(double x, double y, int centerX, int centerY)
{
    double dx=abs(x-centerX);
    double dy=abs(y-centerY);
    double r=double(sqrt(pow(dx,2)+pow(dy,2)));
    //std::cout<<r<<"\n";
    return r;
}

template<typename T>
int DynArry<T>::rotateX(double x, double y, int centerX, int centerY, double fi)
{
    double alpha;
    double r=radius(x, y, centerX, centerY);
    alpha = angle(x, y, centerX, centerY);
    x=((cos((alpha+fi-90) * PI / 180))*r)+centerX;
    x=round(x);
    return x;
}

template<typename T>
int DynArry<T>::rotateY(double x, double y, int centerX, int centerY, double fi)
{
    double r=radius(x, y, centerX, centerY);
    double alpha = angle(x, y, centerX, centerY);
    y=((sin((alpha+fi-90) * PI / 180))*r)+centerY;
    y=round(y);
    return y;
}



#endif // DYNARRY_H
