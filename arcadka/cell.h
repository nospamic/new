#ifndef CELL_H
#define CELL_H
typedef unsigned int un;

class Cell
{
public:
    enum CELLTYPE {BORDER, PLAYER, BILDING, ENEMY, EMPTY};
    Cell();
    char symbol;
    un color;
    un bgColor;
    un type;

};

#endif // CELL_H
