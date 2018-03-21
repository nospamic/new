#include "humanloader.h"

HumanLoader::HumanLoader()
{
    this->path = "humans.txt";
    this->reservPath = "humans_res.txt";

    if(access(path, 0) == -1)
    {
        std::fstream fs;
        fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
        Human men;
        fs<<men;
        fs.close();
    }


    this->size = getSize();
    this->base = new Human[size];
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);

    for(unsigned a=0; a<size; a++) fs>>base[a];
    fs.close();
}

HumanLoader::~HumanLoader()
{
    delete[] base;
}

void HumanLoader::delHuman(int code)
{
    if (existsHuman(code))
    {
        Human* arryNew = new Human[size-1];
        unsigned newSize = 0;
        for(unsigned n=0; n<(size); n++)
        {
            if (base[n].getCode() != code)
            {
                arryNew[newSize] = base[n];
                newSize++;
            }
        }
    delete[] base;
    size--;
    base = arryNew;
    saveBase();
    }
}


bool HumanLoader::existsHuman(int code)
{
    for(unsigned n=0; n<size; n++)
    {
        if (base[n].getCode()==code) return true;
    }
    return false;
}

void HumanLoader::addHuman(std::string name, std::string tel, std::string description, int discount)
{
    Human man;
    man.setCode(100000 + size);
    man.setName(name);
    man.setTel(tel);
    man.setDescription(description);
    man.setDiscount(discount);
    Human * baseNew = new Human[size + 1];
    for(unsigned n=0; n<size; n++) baseNew[n] = base[n];
    baseNew[size] = man;
    delete[] base;
    size=size+1;
    base = new Human[size];
    base = &baseNew[0];

    saveBase();
}


Human HumanLoader::getHuman(int code)
{
    Human result;
    int position = -1;
    for (unsigned n=0; n<size; n++)
    {
        if(base[n].getCode() == code)
        {
            position = n;
            break;
        }
    }
    if(position != -1)
    {
        result = base[position];
    }
    else
    {
        result.setName("Объект не найден");
    }
    return result;
}

void HumanLoader::loadBase()
{
    if (base!=nullptr)delete[] base;
    this->size = getSize();
    this->base = new Human[size];
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);

    for(unsigned a=0; a<size; a++) fs>>base[a];
    fs.close();
}


unsigned HumanLoader::getSize()
{
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
    unsigned length = 0;
    while(true)
    {
        Human h;
        fs >> h;
        if(fs.eof()){break;}else{++length;}
    }
    fs.close();

    return length;
}

void HumanLoader::saveBase()
{
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::trunc);
    !fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<" <--Array \n";

    for(unsigned a=0; a<size; a++) fs<<base[a];
    fs.close();
}

void HumanLoader::saveReserv()
{
    std::fstream fs;
    fs.open(reservPath, std::fstream::in | std::fstream::out | std::fstream::trunc);
    !fs.is_open()?std::cout<<"\nError open "<<reservPath<<"\n":std::cout<<"\nOpen - "<<reservPath<<" <--Array \n";

    for(unsigned a=0; a<size; a++) fs<<base[a];
    fs.close();
}
