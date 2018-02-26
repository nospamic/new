#include "loader.h"

Loader::Loader(void)
{
    path="data.txt";
}


Loader::~Loader(void)
{
}


unsigned Loader::objQuantity(char*path)
{
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
    //!fs.is_open()?exit(0):true;
    unsigned length=0;
    while(true)
    {

        Unit h;
        fs>>h;
        if(fs.eof()){break;}else{++length;}
        //std::cout << h <<"  length="<<length<<"\n";
    }
    fs.close();
    //std::cout <<"\n"<<length<<"\n";
    return length;
}


Unit* Loader::createArr(unsigned size)
{
    Unit *arry = new Unit[size];
    return &arry[0];
}


Unit* Loader::fileToArr(char* path)
{
    unsigned size = objQuantity(path);
    Unit* arry(createArr(size));
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
    for(un a=0; a<size; a++)
    {
        fs>>arry[a];
    }
    fs.close();
    return &arry[0];
}



void Loader::ArrToFile(char* path, Unit* arry,un length)
{

    //std::cout<<length<<"\n";
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::trunc);
    !fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<" <--Array \n";

    for(unsigned a=0; a<length; a++)
    {
        fs<<arry[a];
        //std::cout<<arry[a];
    }
    fs.close();
}


void Loader::makeNewDateFile(char*path, un size)
{
    Unit* arry=createArr(size);
    for(un a=0;a<size;a++)
    {
        std::cout<<arry[a];
    }
    ArrToFile(path,arry,size);
}


void Loader::printArr()
{


    Loader loader;
    Unit*arry=loader.fileToArr(path);

    un size=objQuantity(path);
    std::cout<<"------------Print array. Size:"<<size<<"\n";
    for(un n=0; n<size; n++)
    {
        std::cout<<arry[n];
    }
    std::cout<<"------------ End -----------------\n";
    delete[] arry;
}


void Loader::addUnitToFile(char*path, std::string name = "noname", float price = 0, int quantity = 1, std::string barcode = "-", std::string description = "no_description")
{
    Unit*base=fileToArr(path);
    un size=objQuantity(path);
    un lastId=base[size-1].getId();
    un lastCode=base[size-1].getCode();

    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
    !fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<" <--unit \n";

    Unit unit;
    unit.setId(lastId+1);
    unit.setCode(lastCode+1);
    unit.setName(name);
    unit.setPrice(price);
    unit.setQuantity(quantity);
    unit.setBarcode(barcode);
    unit.setDescription(description);
    fs<<unit;
    fs.close();
    delete[] base;
}

std::string Loader::removeSpaces(std::string str)
{
    std::string result="";
    for(un a=0; a<str.size();a++)
    {
        if (str[a]==' ' || str[a]=='\n') {result.push_back('_');}else {result.push_back(str[a]);}
    }
    return result;
}

void Loader::edit(un code, std::string barcode, int quantity, float price, float echarge, std::string name, std::string section, std::string group, std::string description, un salesPerMonth)
{
    un size = objQuantity(path);
    Unit * base = fileToArr(path);
    int position = -1;
    for (un n=0; n<size; n++)
    {
        if(base[n].getCode() == code)
        {
            position = n;
            break;
        }
    }
    std::cout <<"Write to position: "<<position<<"\n";
    if(position>=0)
    {
        base[position].setBarcode(barcode);
        base[position].setQuantity(quantity);
        base[position].setPrice(price);
        base[position].setEcharge(echarge);
        base[position].setName(name);
        base[position].setSection(section);
        base[position].setGroup(group);
        base[position].setDescription(description);
        base[position].setSalesPerMonth(salesPerMonth);

        ArrToFile(path, &base[0], size);
    }
    delete[] base;
}

Unit Loader::getUnit(un code)
{
    un size = objQuantity(path);
    Unit * base = fileToArr(path);
    int position = -1;
    for (un n=0; n<size; n++)
    {
        if(base[n].getCode() == code)
        {
            position = n;
            break;
        }
    }
    Unit result = base[position];
    delete[] base;
    std::cout<<result<<"\n";
    return result;
}


Unit Loader::getUnit(std::string barcode)
{
    un size = objQuantity(path);
    Unit * base = fileToArr(path);
    Unit result;
    int position = -1;
    for (un n=0; n<size; n++)
    {
        if(base[n].getBarcode() == barcode)
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

        result.setName("nullUnit");
    }
    delete[] base;
    std::cout<<result<<"\n";
    return result;
}


Unit *Loader::selectFromFile(std::string word, int &size)
{
    std::cout<<"word = "<< word <<"  size = "<<size<<"\n";

    int newPos = 0;
    Unit* arry = fileToArr(path);
    for(int n=0; n<size; n++)
    {
        std::string name=arry[n].getName();
        if(name.find(word)<name.size())
        {
            arry[newPos] = arry[n];
            newPos++;
            //result.push_back(arry[n]);
            std::cout<<"find()= "<<name.find(word)<<"   ";
            std::cout<<arry[n]<<"   ";
        }
    }
    size = newPos;
    return &arry[0];
}

std::string Loader::nameByBarcode(std::string barcode)
{
    un size = objQuantity(path);
    Unit* arry = fileToArr(path);
    for(int n=0; n<size; n++)
    {
        if (arry[n].getBarcode()==barcode)
        {
            return arry[n].getName();
        }
    }
    delete[] arry;
    return "";

}

un Loader::getPosition(un code)
{
    un size = objQuantity(path);
    Unit* arry = fileToArr(path);
    for(int n=0; n<size; n++)
    {
        if (arry[n].getCode()==code)
        {
            delete[] arry;
            return n;
        }
    }
    delete[] arry;
    return 100000;
}
