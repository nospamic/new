#include "add.h"

Add::Add(QWidget *parent) : QDialog (parent)
{


     QVBoxLayout * vert = new QVBoxLayout;

     lineName = new QLineEdit;
     lineName->setPlaceholderText("Наименование товара");
     lineName->setFixedWidth(200);
     vert->addWidget(lineName);

     linePrice = new QLineEdit;
     linePrice->setPlaceholderText("Цена (USD)");
     vert->addWidget(linePrice);

     QHBoxLayout * hor1 = new QHBoxLayout;
     QLabel * lab1 = new QLabel("Количество ");
     spinQuant = new QSpinBox;
     hor1->addWidget(lab1);
     hor1->addWidget(spinQuant);
     vert->addLayout(hor1);

     ok = new QPushButton("Add");
     vert->addWidget(ok);

     setLayout(vert);
     this->show();
     connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));
}

void Add::itsOk()
{
   this->close();
}
