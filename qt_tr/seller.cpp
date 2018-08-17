#include "seller.h"

Seller::Seller(QWidget *parent)
    : QDialog(parent)
{
    man.setName("no");
    discount = 0;
    checkSumm = 0;
    this->setWindowTitle("Продавец");
    QRegExp intager("[0-9]{0,14}");
    QRegExp money("[0-9]{1,13}[.,]{0,1}[0-9]{0,2}");
    exchange = uLoad.getUnit(100000).getPrice();

    timer = new QTimer();

    QFont font("Lucida Console",12);
    QFont small("Lucida Console",8);
    this->setFont(font);

    white.setColor(QPalette::Base, Qt::white);
    red.setColor(QPalette::Base, Qt::red);
    yellow.setColor(QPalette::Base, Qt::yellow);
    green.setColor(QPalette::Base, Qt::green);

    QRect r = QApplication::desktop()->screenGeometry();
    this->resize(800, r.height()*0.8);

    this->setStyleSheet("QCheckBox { border: 1px solid gray; padding: 2px }");

    QVBoxLayout *vert = new QVBoxLayout;
    QLabel * lblHead = new QLabel(" Код          Название                                   Цена(грн)       К-во(шт.)");
    lblHead->setFont(small);
    vert->addWidget(lblHead);
    listSearsh = new QListWidget;
    listSearsh->setFont(font);
    vert->addWidget(listSearsh);


    QHBoxLayout *hor1 = new QHBoxLayout;
    lineBarcod = new QLineEdit;
    lineBarcod->setPlaceholderText("Найти...");
    lineBarcod->setAutoFillBackground(true);
    //lineBarcod->setValidator(new QRegExpValidator(intager, this));
    hor1->addWidget(lineBarcod);
    checkBack = new QCheckBox("Возврат");
    hor1->addWidget(checkBack);
    checkDebt = new QCheckBox("Долг");
    checkDebt->setEnabled(false);
    hor1->addWidget(checkDebt);

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
    QPalette yellowLabel;
    yellowLabel.setColor(QPalette::Background, Qt::yellow);
    labelDiscount->setAutoFillBackground(false);
    labelDiscount->setPalette(yellowLabel);

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


    setLayout(vert);

    connect(listSearsh, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addToCheck()));
    connect(listCheck, SIGNAL(clicked(QModelIndex)), this, SLOT(setSpinQuantity()));
    connect(spinQuantity, SIGNAL(valueChanged(int)), this, SLOT(changeQuantity()));
    connect(lineBarcod, SIGNAL(returnPressed()), this, SLOT(barcodeScanned()));
    //connect(lineSearsh, SIGNAL(returnPressed()), this, SLOT(getListSelect()));
    connect(linePay, SIGNAL(returnPressed()), this, SLOT(sold()));
    connect(linePay, SIGNAL(textChanged(QString)), this, SLOT(showChange()));
    connect(buttonDel, SIGNAL(clicked(bool)), this, SLOT(delFromCheck()));
    connect(listCheck, SIGNAL(clicked(QModelIndex)), this, SLOT(delEnable()));
    connect(buttonNext, SIGNAL(clicked(bool)), this, SLOT(nextPressed()));
    connect(listCheck, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(delFromCheck()));
    connect(checkBack, SIGNAL(clicked(bool)), this, SLOT(backClicked()));
    connect(timer, SIGNAL(timeout()),this, SLOT(colorLine()));
    connect(listSearsh, SIGNAL(clicked(QModelIndex)), lineBarcod, SLOT(setFocus()));

    getListSelect();
    lineBarcod->setFocus();
    setTabOrder(lineBarcod, linePay);

    timer->start(500);

}

Seller::~Seller()
{
    timer->stop();
    delete timer;

}


void Seller::getListSelect()
{
    listSearsh->clear();
    QString word = lineBarcod->text();

    std::vector<Unit>base = uLoad.base;
    int size = base.size();

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
        if(listSearsh->count() == 0)
        {
            searsh(textbutor.latinToKiril(word));
        }
    }
    lineBarcod->setFocus();
}


void Seller::sold()
{
    if(textbutor.isBarcode(linePay->text()))
    {
        lineBarcod->setText(linePay->text());
        linePay->clear();
        this->barcodeScanned();
    }
    else if(check.size()>0 && textbutor.toDot(linePay->text()).toFloat() >= checkSumm - uLoad.round(checkSumm*discount/100))
    {
        uLoad.load();

        for(unsigned n=0; n<check.size(); n++)
        {
            unsigned position = uLoad.getPosition(check[n].getCode());
            uLoad.base[position].setQuantity(uLoad.base[position].getQuantity() - quantity[n]);
            uLoad.base[position].addSales(quantity[n]);

        }
        uLoad.save();

        printCheck();
        man.setSumm(man.getSumm() + checkSumm - uLoad.round(checkSumm*discount/100));
        if (man.getName()!="no")humanloader.edit(man);

        uLoad.addToLog(createLog());
        reset();
        QApplication::beep();
    }
}


void Seller::showChange()
{
    float change = textbutor.toDot(linePay->text()).toFloat() - (checkSumm - uLoad.round(checkSumm*discount/100));
    change = round(change*100)/100;
    QString qchange;
    if(linePay->text().isEmpty() || textbutor.toDot(linePay->text()).toFloat() <= (checkSumm - uLoad.round(checkSumm*discount/100)))
    {
        qchange = "Сдача: --";
    }
    else
    {
        qchange = "Сдача: " + QString::number(change) + " грн.";
        this->changeHelp(change);
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
   reset();
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

    std::vector<Unit>vBase = uLoad.base;

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
    if (discount > 0) qResult +="Скидка: " + QString::number(uLoad.round(checkSumm*discount/100))+"\n";
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


void Seller::backClicked()
{
    if(checkBack->isChecked())
    {
        this->lineBarcod->setPalette(red);
        this->lineBarcod->setFocus();
    }
    else
    {
        this->lineBarcod->setPalette(white);
        this->lineBarcod->setFocus();
    }
}


void Seller::colorLine()
{
    lineBarcod->hasFocus() ? lineBarcod->setPalette(green): lineBarcod->setPalette(white);
    if (checkBack->isChecked()) lineBarcod->setPalette(red);
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
                price = uLoad.round(check[n].getPrice());
            }
            else
            {
                price = uLoad.round(check[n].getPrice() * exchange);
            }
            QString QPrice = textbutor.cutter(QString::number(price),10);
            QString QPriceXQuantity = QString::number(price * quantity[n]);

            QString toList = QName + "  " + QQuantity + "x " + QPrice + " = " + QPriceXQuantity;
            listCheck->addItem(toList);
            checkSumm += int(price * quantity[n]);
        }
        int checkResult = checkSumm - uLoad.round(checkSumm*discount/100);
        QString summ = "К оплате: " + QString::number(checkResult) + " грн.";
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

    QString qResult ="--------------------" + dateTime + "--------------------" + QString::number(uLoad.getBalance()) + "\n\n";
    unsigned size = check.size();
    for(unsigned n=0; n<size; n++)
    {
        qResult += listCheck->item(n)->text();
        qResult += "\n";
    }
    qResult += "----------------------------------------------------------------------\n";
    if (discount > 0) qResult +="Скидка = -" + QString::number(uLoad.round(checkSumm*discount/100)) + "\n";
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
        price = uLoad.round(unit.getPrice());
    }
    else
    {
        price = uLoad.round(unit.getPrice() * exchange);
    }
    return QString::number(price);
}


void Seller::changeHelp(float change)
{
    int tail = change - int(change/100)*100;
    if(tail >= 30 && tail < 50)
    {
        QString text = "Дайте " + QString::number(50 - tail) + " грн.";
        this->lineManInfo->setText(text);
    }
    else if(tail >= 8 && tail < 10)
    {
        QString text = "Дайте " + QString::number(10 - tail) + " грн.";
        this->lineManInfo->setText(text);
    }

}


void Seller::reset()
{
    check.clear();
    quantity.clear();
    listCheck->clear();
    labelSumm->setText("К оплате: --");
    linePay->clear();
    labelChange->setText("Сдача: --");
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


void Seller::addToCheck()
{
    QString strCode = listSearsh->currentItem()->text();
    strCode = strCode.left(6);
    int code = strCode.toInt();
    Unit item = uLoad.getUnit(code);
    check.push_back(item);
    !checkBack->isChecked()?quantity.push_back(1):quantity.push_back(-1);
    checkShow();
    checkBack->setChecked(false);
    this->backClicked();
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
    if(!textbutor.isBarcode(barcode) && barcode != "")
    {
        this->getListSelect();
    }
    else if(barcode.left(6)=="575757")
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
        unit = uLoad.getUnit(barcode.toLocal8Bit().constData());
        check.push_back(unit);
        !checkBack->isChecked()?quantity.push_back(1):quantity.push_back(-1);
        checkBack->setChecked(false);
        this->backClicked();
    }
    lineBarcod->clear();
    checkShow();
    lineBarcod->setFocus();

}


