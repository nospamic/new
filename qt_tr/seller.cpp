#include "seller.h"

Seller::Seller(QWidget *parent)
    : QDialog(parent)
{
    man.setName("no");
    discount = 0;
    checkSumm = 0;
    this->setWindowTitle("Продавец");
    QRegExp intager("[0-9]{0,14}");
    QRegExp money("[0-9]{1,4}[.,]{0,1}[0-9]{0,2}");
    exchange = loader.getUnit(100000).getPrice();

    QFont font("Lucida Console",12);
    QFont small("Lucida Console",8);
    this->setFont(font);


    QRect r = QApplication::desktop()->screenGeometry();
    this->resize(800, r.height()*0.8);


    QVBoxLayout *vert = new QVBoxLayout;
    QLabel * lblHead = new QLabel(" Код          Название                                   Цена(грн)       К-во(шт.)");
    lblHead->setFont(small);
    vert->addWidget(lblHead);
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
    QVBoxLayout *vert0 = new QVBoxLayout;
    listCheck = new QListWidget;
    listCheck->setFont(font);
    vert0->addWidget(listCheck);
    lineManInfo = new QLineEdit;
    lineManInfo->setFont(small);
    lineManInfo->setDisabled(true);
    vert0->addWidget(lineManInfo);
    hor2->addLayout(vert0);

    QVBoxLayout *vert2 = new QVBoxLayout;
    spinQuantity = new QSpinBox;
    spinQuantity->setMaximum(999);
    spinQuantity->setEnabled(false);
    buttonDel = new QPushButton("X");
    buttonDel->setEnabled(false);
    buttonDel->setAutoDefault(false);
    vert2->addWidget(spinQuantity);
    vert2->addWidget(buttonDel);
    labelDiscount = new QLabel;
    QPalette yellow;
    yellow.setColor(QPalette::Background, Qt::yellow);

    labelDiscount->setAutoFillBackground(false);
    labelDiscount->setPalette(yellow);

    vert2->addWidget(labelDiscount);
    buttonNext = new QPushButton;
    QPixmap pixmap("next.bmp");
    QIcon ButtonIcon(pixmap);
    buttonNext->setIcon(ButtonIcon);
    buttonNext->setIconSize(pixmap.rect().size());
    vert2->addWidget(buttonNext);
    buttonNext->setEnabled(false);
    buttonNext->setAutoDefault(false);
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

    //labelManInfo = new QLabel;
    //vert->addWidget(labelManInfo);
    //labelManInfo->setFont(small);



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
    connect(buttonNext, SIGNAL(clicked(bool)), this, SLOT(nextPressed()));
    connect(listCheck, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(delFromCheck()));

    getListSelect();
    lineBarcod->setFocus();
    setTabOrder(lineBarcod, linePay);

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
            QString price = textbutor.cutter(getQPrice(base[n]),9);
            QString quantity = QString::number(base[n].getQuantity());
            listSearsh->addItem(code+"   "+name+"  "+price+" "+quantity);
        }
    }
    else
    {
        searsh(word);
    }
    lineBarcod->setFocus();
}


void Seller::sold()
{
    if(check.size()>0 && textbutor.toDot(linePay->text()).toFloat() >= checkSumm)
    {
        int size = loader.size;
        Unit *base = loader.base;
        for(unsigned n=0; n<check.size(); n++)
        {
            unsigned position = loader.getPosition(check[n].getCode());
            base[position].setQuantity(base[position].getQuantity() - quantity[n]);
        }
        loader.ArrToFile(base, size);

        printCheck();
        man.setSumm(man.getSumm() + checkSumm - int(checkSumm*discount/100));
        humanloader.edit(man);
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
        this->discount = 0;
        labelDiscount->clear();
        labelDiscount->setAutoFillBackground(false);
        man.setName("no");
        lineManInfo->clear();
        buttonNext->setEnabled(false);
        checkSumm = 0;
        QApplication::beep();
    }
}

void Seller::showChange()
{
    float change = textbutor.toDot(linePay->text()).toFloat() - checkSumm;
    change = round(change*100)/100;
    QString qchange;
    if(linePay->text().isEmpty() || textbutor.toDot(linePay->text()).toFloat() <= checkSumm)
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
    lineBarcod->setFocus();
    checkShow();
}

void Seller::delEnable()
{
    buttonDel->setEnabled(true);
    buttonDel->setAutoDefault(false);
    spinQuantity->setEnabled(true);
}

void Seller::humanTest(QString barcode)
{
    humanloader.loadBase();
    int code = barcode.mid(6, 6).toInt();
    Human man = humanloader.getHuman(code);
    if(man.getTel().substr(0,1) == "!")
    {
        HumanEdit * edit = new HumanEdit(code, true, this);
        edit->show();
        edit->exec();
        humanloader.loadBase();
    }
    this->man = humanloader.getHuman(code);
    manShow();
    buttonNext->setEnabled(true);
}

void Seller::manShow()
{
    if(this->man.getName() != "no")
    {
        QString qDiscount = QString::number(int(checkSumm*discount/100));
        QString manInfo = "Скидка:" + qDiscount + " грн.    " + QString::fromLocal8Bit((this->man.getName()).c_str())
        + "     Долг:" + QString::number(this->man.getDebt()) + " грн.";
        lineManInfo->setText(manInfo);
    }
}

void Seller::nextPressed()
{
    check.clear();
    quantity.clear();
    listCheck->clear();
    labelSumm->setText("К оплате: --");
    linePay->clear();
    labelChange->setText("Сдача: --");
    lineSearsh->clear();
    getListSelect();
    lineBarcod->setFocus();
    this->discount = 0;
    labelDiscount->clear();
    labelDiscount->setAutoFillBackground(false);
    man.setName("no");
    lineManInfo->clear();
    buttonNext->setEnabled(false);
    checkSumm = 0;
}

void Seller::searsh(QString word)
{
    word = word.toLower();


    std::vector<QString>whatSearsh;
    QString add = "";
    for(int n=0; n<word.size(); n++)
    {
        if(word.mid(n,1)!=" "){add+=word.mid(n,1);}
        else
            if(add.size()>0)
            {
                whatSearsh.push_back(add);
                add = "";
            }
    }
    if(add.size()>0) whatSearsh.push_back(add);

    std::vector<Unit>vBase;
    for (unsigned n=0; n<loader.size; n++)vBase.push_back(loader.base[n]);

    int size =  whatSearsh.size();
    //qDebug()<<"Size="<<size;
    for(int n = size-1; n >= 0; n--)
    {
        for(unsigned i=0; i<vBase.size(); i++)
        {
            int coincidence = 0;
            QString name = QString::fromLocal8Bit((vBase[i].getName()).c_str());
            for(int a=0; a<size; a++)
            {
                if(name.contains(whatSearsh[a], Qt::CaseInsensitive)){coincidence++;}
            }
            //if(coincidence>0)qDebug()<<"совпадений-"<<coincidence;
            if (coincidence==(n+1))
            {
                QString code = QString::number(vBase[i].getCode());
                QString name = textbutor.cutter(QString::fromLocal8Bit((vBase[i].getName()).c_str()),30);
                QString price = textbutor.cutter(getQPrice(vBase[i]),9);
                QString quantity = QString::number(vBase[i].getQuantity());
                listSearsh->addItem(code+"   "+name+"  "+price+" "+quantity);
                vBase.erase(vBase.begin()+i);
                i--;
            }
        }

    }




}

void Seller::printCheck()
{
    QDateTime dt = QDateTime::currentDateTime();
    QString dateTime = dt.toString();
    QString qResult = "--------------------------------\n";
    qResult += "Магазин Motoroller\n";
    qResult += "Адрес: Ильичевская дор, 1\n";
    qResult += "--------------------------------\n";
    qResult +="\n\n--" + dateTime + "--" + "\n\n";
    unsigned size = check.size();
    for(unsigned n=0; n<size; n++)
    {
        qResult += listCheck->item(n)->text().left(32);
        qResult +="= ";
        qResult +=listCheck->item(n)->text().mid(40,6);
        qResult += "\n";
    }
    qResult += "--------------------------------\n";
    if (discount > 0) qResult +="Скидка: " + QString::number(loader.round(checkSumm*discount/100))+"\n";
    qResult +=labelSumm->text() + "\n\n\n";
    qResult += "--------------------------------\n";
    qResult += "Товары со следами эксплуатации, ремонта,\n";
    qResult += "автохимия, краски в аэрозольных баллонах,\n";
    qResult += "товары без оригинальной упаковки\n";
    qResult += "обмену и возврату не подлежат!!!\n";
    qResult += "\n--------------------------------\n";

#ifndef QT_NO_PRINTER
    QFont small("Lucida Console",6);
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageMargins(QMarginsF(0,0,0,0));
    QPainter paint(&printer);
    paint.setPen(Qt::black);
    paint.setFont(small);
    paint.drawText(QRect(0, 0, 450, 900), Qt::AlignLeft, qResult);
#endif
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
        //buttonNext->setEnabled(false);
    }
    else
    {
        buttonDel->setAutoDefault(false);
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
                price = loader.round(check[n].getPrice());
            }
            else
            {
                price = loader.round(check[n].getPrice() * exchange);
            }
            QString QPrice = textbutor.cutter(QString::number(price),10);
            QString QPriceXQuantity = QString::number(price * quantity[n]);

            QString toList = QName + "  " + QQuantity + "x " + QPrice + " = " + QPriceXQuantity;
            listCheck->addItem(toList);
            checkSumm += int(price * quantity[n]);
        }
        checkSumm -=loader.round(checkSumm*discount/100);
        QString summ = "К оплате: " + QString::number(checkSumm) + " грн.";
        labelSumm->setText(summ);
        showChange();
        manShow();
        buttonNext->setEnabled(true);
        buttonNext->setAutoDefault(false);
        lineBarcod->setFocus();
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
    if (discount > 0) qResult +="Скидка:" + QString::number(loader.round(checkSumm*discount/100))+"\n";
    qResult +=labelSumm->text();
    qResult +="\t Оплачено: " + linePay->text() + "грн.";
    qResult +="\t" + labelChange->text() + "\n\n\n";

    return qResult.toLocal8Bit().constData();
}


QString Seller::getQPrice(Unit unit)
{
    float price;
    if(isUah(unit))
    {
        price = loader.round(unit.getPrice());
    }
    else
    {
        price = loader.round(unit.getPrice() * exchange);
    }
    return QString::number(price);
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
    Unit unit;
    QString barcode = lineBarcod->text();
    if(barcode.left(6)=="575757")
    {
        humanTest(barcode);
        int code = barcode.mid(6, 6).toInt();
        Human man = humanloader.getHuman(code);
        discount = man.getDiscount();
        QString disc = "  "  + QString::number(discount) + " %";
        labelDiscount->setAutoFillBackground(true);
        labelDiscount->setText(disc);
        qDebug()<<"discount = "<<discount;
    }
    else if(barcode=="")
    {
        linePay->setText(QString::number(checkSumm));
        sold();
    }
    else
    {
        unit = loader.getUnit(barcode.toLocal8Bit().constData());
        check.push_back(unit);
        quantity.push_back(1);
    }
    lineBarcod->clear();
    checkShow();
    lineBarcod->setFocus();

}


