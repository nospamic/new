#ifndef DYNARRY_H
#define DYNARRY_H

#include <vector>
typedef unsigned int un;


template <typename T>
class DynArry
{
public:
    DynArry(un sizeX, un sizeY, T fill);
    //~DynArry();
    T getElement(un xPos, un yPos);
    void setElement(un xPos, un yPos, T);
    un sizeX, sizeY;
private:

    T fill;
    std::vector<T>base;
    void create();
};


template <typename T>
DynArry<T>::DynArry(un sizeX, un sizeY, T fill)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->fill = fill;
    this->create();
}


//template <typename T>
//DynArry<T>::~DynArry()
//{
//}


template <typename T>
 void DynArry<T>::create()
{
    for (un y = 0; y < sizeY; y++)
    {
        for (un x = 0; x < sizeX; x++) base.push_back(fill);
    }
}


template <typename T>
T DynArry<T>::getElement(un xPos, un yPos)
{
    return base[sizeY*yPos + xPos];
}


template <typename T>
void DynArry<T>::setElement(un xPos, un yPos, T value)
{
    base[sizeY*yPos + xPos] = value;
}



#endif // DYNARRY_H
