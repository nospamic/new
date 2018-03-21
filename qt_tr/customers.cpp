#include "customers.h"

Customers::Customers(QWidget *parent)
    : QDialog(parent)
{
    QFont font("Lucida Console",12);
    this->setFont(font);
    this->setWindowTitle("Клиенты");
    this->setFixedWidth(620);
    QVBoxLayout * vert = new QVBoxLayout;

    list = new QListWidget;
    vert->addWidget(list);
    list->setFont(font);

    QHBoxLayout * hor = new QHBoxLayout;

    lineSearsh = new QLineEdit;
    hor->addWidget(lineSearsh);

    buttonAdd = new QPushButton("Добавить");
    hor->addWidget(buttonAdd);

    buttonEdit = new QPushButton("Редактировать");
    hor->addWidget(buttonEdit);

    buttonDelete = new QPushButton("Удалить");
    hor->addWidget(buttonDelete);

    vert->addLayout(hor);

    setLayout(vert);

    getListSelect();

    buttonAdd->setAutoDefault(false);
    buttonDelete->setEnabled(false);
    buttonEdit->setEnabled(false);
    lineSearsh->setFocus();

    connect(buttonAdd, SIGNAL(clicked(bool)), this, SLOT(addHuman()));
    connect(buttonDelete, SIGNAL(clicked(bool)), this, SLOT(delHuman()));
    connect(buttonEdit, SIGNAL(clicked(bool)), this, SLOT(editHuman()));
    connect(lineSearsh, SIGNAL(returnPressed()), this, SLOT(selectHuman()));
    connect(list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editHuman()));
    connect(list, SIGNAL(clicked(QModelIndex)), this, SLOT(setDelEditEnable()));

}

Customers::~Customers()
{

}

void Customers::getListSelect()
{
    list->clear();
    QString word = lineSearsh->text();
    int size = humanloader.size;
    Human *base = humanloader.base;

    if (word.isEmpty())
    {
        for(int n=0; n<size; n++)
        {
            QString code = QString::number(base[n].getCode());
            QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),20);
            QString tel = textbutor.cutter(QString::fromLocal8Bit((base[n].getTel()).c_str()),14);
            QString discount = textbutor.cutter(QString::number(base[n].getDiscount())+"%", 4);
            QString debt = textbutor.cutter(QString::number(base[n].getDebt()) + "грн.", 6);
            list->addItem(code+"  " + name + "  " + discount + "  " + debt + "  " + tel);
        }
    }
    else
    {
        word = word.toLower();
        for(int n=0; n<size; n++)
        {
            QString code = QString::number(base[n].getCode());
            QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),20);
            QString tel = textbutor.cutter(QString::fromLocal8Bit((base[n].getTel()).c_str()),14);
            QString discount = textbutor.cutter(QString::number(base[n].getDiscount())+"%", 4);
            QString debt = textbutor.cutter(QString::number(base[n].getDebt()) + "грн.", 6);

            if (name.contains(word, Qt::CaseInsensitive))
            {
                list->addItem(code+"  " + name + "  " + discount + "  " + debt + "  " + tel);
            }
        }
    }

    buttonEdit->setEnabled(false);
    buttonDelete->setEnabled(false);
}

void Customers::addHuman()
{
    HumanAdd * add = new HumanAdd(this);
    add->show();
    add->exec();
    humanloader.loadBase();
    getListSelect();
}

void Customers::editHuman()
{

}

void Customers::delHuman()
{
    int code = list->currentItem()->text().left(6).toInt();
    humanloader.delHuman(code);
    getListSelect();
}

void Customers::selectHuman()
{
    getListSelect();
}

void Customers::setDelEditEnable()
{
    buttonDelete->setEnabled(true);
    buttonEdit->setEnabled(true);
}
