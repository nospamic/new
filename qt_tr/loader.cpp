#include "loader.h"

Loader::Loader(void)
{

    path="data.txt";
    reservPath = "res_data.txt";
    logPath = "LOG\\day_"+ getDate() + ".log";

    base = fileToArr();
    size = objQuantity();
}


Loader::~Loader(void)
{
    delete[] base;
}


unsigned Loader::objQuantity()
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


Unit* Loader::fileToArr()
{
    unsigned size = objQuantity();
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



void Loader::ArrToFile(Unit* arry, un length)
{


    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::trunc);
    !fs.is_open()?std::cout<<"\nError open "<<path<<"\n":std::cout<<"\nOpen - "<<path<<" <--Array \n";

    for(unsigned a=0; a<length; a++)
    {
        fs<<arry[a];

    }
    fs.close();
}


void Loader::makeNewDateFile(un size)
{
    Unit* arry=createArr(size);
    for(un a=0;a<size;a++)
    {
        arry[a].setCode(100000+a);
        arry[a].setName("$$$");
    }
    ArrToFile(arry, size);
    fillBase();
}


void Loader::printArr()
{
    std::cout<<"------------Print array. Size:"<<size<<"\n";
    for(un n=0; n<size; n++)std::cout<<base[n];
    std::cout<<"------------ End -----------------\n";
}


void Loader::addUnitToFile(std::string name = "noname", float price = 0, int quantity = 1, std::string barcode = "0000000000000", std::string description = "no_description")
{
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

    fillBase();
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

        ArrToFile(&base[0], size);
    }

    fillBase();
}

Unit Loader::getUnit(un code)
{

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

    return result;
}


Unit Loader::getUnit(std::string barcode)
{

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
    return result;
}


std::string Loader::nameByBarcode(std::string barcode)
{

    std::string result = "";
    for(un n=0; n<size; n++)
    {
        if (base[n].getBarcode()==barcode)
        {
            result =  base[n].getName();
            return result;
        }
    }
    return result;
}

un Loader::getPosition(un code)
{
    for(un n=0; n<size; n++)
    {
        if (base[n].getCode()==code) return n;
    }
    return 100000;
}


bool Loader::fileExists()
{
    //std::cout<<access(path, 0);
    //return access(path, 0) != -1;
    return size!=0;
}


bool Loader::unitExists(un code)
{
    for(un n=0; n<size; n++)
    {
        if (base[n].getCode()==code) return true;
    }
    return false;
}

bool Loader::unitExists(std::string barcode)
{
    for(un n=0; n<size; n++)
    {
        if (base[n].getBarcode() == barcode) return true;
    }
    return false;
}

void Loader::delUnit(un code)
{
    if (unitExists(code))
    {
        Unit* arryNew = new Unit[size-1];
        un newSize = 0;
        for(un n=0; n<(size); n++)
        {
            if (base[n].getCode() != code)
            {
                arryNew[newSize] = base[n];
                newSize++;
            }
        }
    ArrToFile(arryNew, newSize);
    delete[] arryNew;
    fillBase();
    }
}


un Loader::getLastCode()
{
    un size = objQuantity();
    Unit* arry = fileToArr();
    return arry[size-1].getCode();
}


void Loader::addToLog(std::string msg)
{
    if(!QDir("LOG").exists())
        QDir().mkdir("LOG");
    std::fstream log;
    log.open(logPath, std::fstream::in | std::fstream::out | std::fstream::app);
    log<<msg;

}

std::string Loader::getDate()
{
    struct tm *date;
    time_t t = time(NULL);
    date = gmtime(&t);
    int day =date->tm_mday;
    int month = date->tm_mon+1;
    int year = date->tm_year+1900;
    //std::cout<<date->tm_hour<<':'<<date->tm_min<<':'<<date->tm_sec;
    std::string date1 = std::to_string(day) + "_" + std::to_string(month) + "_" + std::to_string(year);
    return date1;
}

float Loader::getBalance()
{
    float balance = 0;
    un size = objQuantity();
    Unit* arry = fileToArr();
    for(un n=1; n<size; n++)
    {
       if(arry[n].getDescription().substr(0,1)=="#")
       {
           balance += arry[n].getPrice() * arry[n].getQuantity();
       }
       else
       {
           balance += arry[n].getPrice() * arry[n].getQuantity() * arry[0].getPrice();
       }
    }
    delete[] arry;
    return balance;
}

void Loader::makeReservCopy()
{
    un length = objQuantity();
    Unit *base = fileToArr();

    std::fstream fs;
    fs.open(reservPath, std::fstream::in | std::fstream::out | std::fstream::trunc);
    !fs.is_open()?std::cout<<"\nError open "<<reservPath<<"\n":std::cout<<"\nOpen - "<<reservPath<<" <--Array \n";
    for(unsigned a=0; a<length; a++) fs<<base[a];
    fs.close();

    delete[] base;
}

void Loader::fillBase()
{
    if (this->base != nullptr) delete[] this->base;
    this->base = fileToArr();
    this->size = objQuantity();
}





