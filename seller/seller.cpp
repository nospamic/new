#include "seller.h"

Seller::Seller(QWidget *parent)
    : QDialog(parent)
{
    path="data.txt";

    QFont font("Lucida Console",9);
    this->setFont(font);
    QVBoxLayout *vert = new QVBoxLayout;
    listSearsh = new QListWidget;
    listSearsh->setFont(font);
    getListSelect("");
    vert->addWidget(listSearsh);


    QHBoxLayout *hor1 = new QHBoxLayout;

    lineBarcod = new QLineEdit;
    lineBarcod->setPlaceholderText("Штрихкод...");
    hor1->addWidget(lineBarcod);
    lineSearsh = new QLineEdit;
    lineSearsh->setPlaceholderText("Найти...");
    hor1->addWidget(lineSearsh);
    buttonSearsh = new QPushButton(">>");
    hor1->addWidget(buttonSearsh);

    vert->addLayout(hor1);

    QHBoxLayout *hor2 = new QHBoxLayout;
    listCheck = new QListWidget;
    hor2->addWidget(listCheck);

    QVBoxLayout *vert2 = new QVBoxLayout;
    spinQuantity = new QSpinBox;
    buttonDel = new QPushButton("X");
    vert2->addWidget(spinQuantity);
    vert2->addWidget(buttonDel);
    hor2->addLayout(vert2);

    vert->addLayout(hor2);


    setLayout(vert);

    connect(listSearsh, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addToCheck()));
}

Seller::~Seller()
{

}

void Seller::getListSelect(QString word = "")
{
    if (word=="")
    {
        int size = loader.objQuantity(path);
        Unit *base = loader.fileToArr(path);
        for(int n=0; n<size; n++)
        {
            QString code = QString::number(base[n].getCode());
            QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),30);

            QString price = QString::number(base[n].getPrice());
            QString quantity = QString::number(base[n].getQuantity());
            listSearsh->addItem(code+"   "+name+" "+price+"\t   "+quantity);

        }

    }
    else
    {

    }
}

void Seller::addToCheck()
{
    QString strCode = listSearsh->currentItem()->text();
    strCode = strCode.left(6);
    int code = strCode.toInt();
    Unit item = loader.getUnit(code);
    check.push_back(item);
    listCheck->clear();
    for(int n=0; n<check.size(); n++)
    {
        QString QCode = QString::number(check[n].getCode());
        QString QName = QString::fromLocal8Bit((check[n].getName()).c_str());
        QString toList = QCode + " " + QName;
        listCheck->addItem(toList);
    }
}


