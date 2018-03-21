#include "seller.h"

Seller::Seller(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("Продавец");
    QRegExp intager("[0-9]{10,14}");
    QRegExp money("[0-9]{1,4}[.]{0,1}[0-9]{0,2}");
    exchange = loader.getUnit(100000).getPrice();

    QFont font("Lucida Console",12);
    this->setFont(font);
    this->setFixedWidth(600);
    QVBoxLayout *vert = new QVBoxLayout;
    listSearsh = new QListWidget;
    listSearsh->setFont(font);
    vert->addWidget(listSearsh);


    QHBoxLayout *hor1 = new QHBoxLayout;

    lineBarcod = new QLineEdit;
    lineBarcod->setPlaceholderText("Штрихкод...");
    lineBarcod->setValidator(new QRegExpValidator(intager, this));
    hor1->addWidget(lineBarcod);
    lineSearsh = new QLineEdit;
    lineSearsh->setPlaceholderText("Найти...");
    hor1->addWidget(lineSearsh);
    buttonSearsh = new QPushButton(">>");
    //hor1->addWidget(buttonSearsh);

    vert->addLayout(hor1);

    QHBoxLayout *hor2 = new QHBoxLayout;
    listCheck = new QListWidget;
    listCheck->setFont(font);
    hor2->addWidget(listCheck);

    QVBoxLayout *vert2 = new QVBoxLayout;
    spinQuantity = new QSpinBox;
    spinQuantity->setMaximum(999);
    spinQuantity->setEnabled(false);
    buttonDel = new QPushButton("X");
    buttonDel->setEnabled(false);
    vert2->addWidget(spinQuantity);
    vert2->addWidget(buttonDel);
    hor2->addLayout(vert2);

    vert->addLayout(hor2);

    QHBoxLayout *hor3 = new QHBoxLayout;
    labelSumm = new QLabel("Сумма: --");
    linePay = new QLineEdit;
    linePay->setValidator(new QRegExpValidator(money, this));
    linePay->setPlaceholderText("Оплачено...");
    labelChange = new QLabel("Сдача: --");
    hor3->addWidget(labelSumm);
    hor3->addWidget(linePay);
    hor3->addWidget(labelChange);

    vert->addLayout(hor3);

    setLayout(vert);

    connect(listSearsh, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addToCheck()));
    connect(listCheck, SIGNAL(clicked(QModelIndex)), this, SLOT(setSpinQuantity()));
    connect(spinQuantity, SIGNAL(valueChanged(int)), this, SLOT(changeQuantity()));
    connect(lineBarcod, SIGNAL(returnPressed()), this, SLOT(barcodeScanned()));
    connect(lineSearsh, SIGNAL(returnPressed()), this, SLOT(getListSelect()));
    connect(linePay, SIGNAL(returnPressed()), this, SLOT(sold()));
    connect(linePay, SIGNAL(textChanged(QString)), this, SLOT(showChange()));
    connect(buttonDel, SIGNAL(clicked(bool)), this, SLOT(delFromCheck()));
    connect(listCheck, SIGNAL(clicked(QModelIndex)), this, SLOT(delEnable()));

    getListSelect();
    lineBarcod->setFocus();
}

Seller::~Seller()
{

}

void Seller::getListSelect()
{
    listSearsh->clear();
    QString word = lineSearsh->text();
    int size = loader.size;
    Unit *base = loader.base;

    if (word.isEmpty())
    {
        for(int n=1; n<size; n++)
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
        word = word.toLower();
        for(int n=0; n<size; n++)
        {
            QString code = QString::number(base[n].getCode());
            QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),30);
            QString price = QString::number(base[n].getPrice());
            QString quantity = QString::number(base[n].getQuantity());
            if (name.contains(word, Qt::CaseInsensitive))
            {
                listSearsh->addItem(code+"   "+name+" "+price+"\t   "+quantity);
            }
        }

    }

}


void Seller::sold()
{
    if(check.size()>0 && linePay->text().toFloat() >= checkSumm)
    {
        int size = loader.size;
        Unit *base = loader.base;
        for(unsigned n=0; n<check.size(); n++)
        {
            unsigned position = loader.getPosition(check[n].getCode());
            base[position].setQuantity(base[position].getQuantity() - quantity[n]);
        }
        loader.ArrToFile(base, size);


        loader.addToLog(createLog());
        check.clear();
        quantity.clear();
        listCheck->clear();
        labelSumm->setText("К оплате: --");
        linePay->clear();
        labelChange->setText("Сдача: --");
        lineSearsh->clear();
        getListSelect();
        lineBarcod->setFocus();
    }
}

void Seller::showChange()
{
    float change = linePay->text().toFloat() - checkSumm;
    change = round(change*100)/100;
    QString qchange;
    if(linePay->text().isEmpty() || linePay->text().toFloat() <= checkSumm)
    {
        qchange = "Сдача: --";
    }
    else
    {
        qchange = "Сдача: " + QString::number(change) + " грн.";
    }

    labelChange->setText(qchange);
}

void Seller::delFromCheck()
{
    if(check.size()>1)
    {
        int position = listCheck->currentRow();
        check.erase(check.begin()+position);
        quantity.erase(quantity.begin()+position);
    }
    else
    {
        check.clear();
        quantity.clear();
    }
    buttonDel->setEnabled(false);
    checkShow();
}

void Seller::delEnable()
{
    buttonDel->setEnabled(true);
    spinQuantity->setEnabled(true);
}


void Seller::checkShow()
{
    if(check.size()==0)
    {
        buttonDel->setEnabled(false);
        spinQuantity->setEnabled(false);
        listCheck->clear();
        checkSumm = 0;
        labelSumm->setText("К оплате: --");
        labelChange->setText("Сдача: --");
    }
    else
    {
        //buttonDel->setEnabled(true);
        findRepeat();
        listCheck->clear();
        checkSumm = 0;
        for(unsigned n=0; n<check.size(); n++)
        {
            //QString QCode = QString::number(check[n].getCode());
            QString QName = textbutor.cutter(QString::fromLocal8Bit((check[n].getName()).c_str()), 20);
            QString QQuantity = textbutor.cutter(QString::number(quantity[n]), 3);
            float price;
            if(isUah(check[n]))
            {
                price = check[n].getPrice();
            }
            else
            {
                price = check[n].getPrice() * exchange;
            }
            QString QPrice = textbutor.cutter(QString::number(price),10);
            QString QPriceXQuantity = QString::number(price * quantity[n]);

            QString toList = QName + "  " + QQuantity + "x " + QPrice + " = " + QPriceXQuantity;
            listCheck->addItem(toList);
            checkSumm += price * quantity[n];
        }
        QString summ = "К оплате: " + QString::number(checkSumm) + " грн.";
        labelSumm->setText(summ);
        showChange();
    }
}

bool Seller::isUah(Unit unit)
{
    if (unit.getDescription().substr(0,1)=="+" || unit.getDescription().substr(0,1)=="#")
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Seller::findRepeat()
{
    Unit item = check[check.size()-1];
    for(unsigned n=0; n<(check.size()-1); n++)
    {
        if(item.getCode()==check[n].getCode())
        {
            quantity[n]++;
            check.pop_back();
            quantity.pop_back();
        }
    }

}

std::string Seller::createLog()
{
    QDateTime dt = QDateTime::currentDateTime();
    QString dateTime = dt.toString();

    QString qResult ="--------------------" + dateTime + "--------------------" + QString::number(loader.getBalance()) + "\n\n";
    unsigned size = check.size();
    for(unsigned n=0; n<size; n++)
    {
        qResult += listCheck->item(n)->text();
        qResult += "\n";
    }
    qResult += "----------------------------------------------------------------------\n";
    qResult +=labelSumm->text();
    qResult +="\t Оплачено: " + linePay->text() + "грн.";
    qResult +="\t" + labelChange->text() + "\n\n\n";

    return qResult.toLocal8Bit().constData();
}


void Seller::addToCheck()
{
    QString strCode = listSearsh->currentItem()->text();
    strCode = strCode.left(6);
    int code = strCode.toInt();
    Unit item = loader.getUnit(code);
    check.push_back(item);
    quantity.push_back(1);
    checkShow();
    buttonDel->setEnabled(false);
    spinQuantity->setEnabled(false);
}

void Seller::setSpinQuantity()
{
    int position = listCheck->currentRow();
    int quant = quantity[position];
    spinQuantity->setValue(quant);
    listCheck->setCurrentRow(position);
}

void Seller::changeQuantity()
{
    int position = listCheck->currentRow();
    quantity[position] = spinQuantity->value();
    checkShow();
    listCheck->setCurrentRow(position);
}

void Seller::barcodeScanned()
{
    QString barcode = lineBarcod->text();
    Unit unit = loader.getUnit(barcode.toLocal8Bit().constData());
    check.push_back(unit);
    quantity.push_back(1);
    lineBarcod->clear();
    checkShow();
    lineBarcod->setFocus();

}


