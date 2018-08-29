#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->isQueue = new bool;
    *isQueue = false;
    this->state = "normal";
    ui->setupUi(this);
    this->setWindowTitle("Склад");
    QFont font("Lucida Console",10);
    this->setFont(font);

    timerSeller = new QTimer();
    wait = 60000;
    timerSeller->start(wait);


    if(!uLoad.fileExists())
    {
        QMessageBox msg;
        msg.setText("Файл data.txt не существует. Создаю новый.");
        msg.exec();
        uLoad.newFile();
    }

    //------------------------------------------------------------------

    //QString s = QString::number(i);
    // QString name=QString::fromLocal8Bit((str).c_str());
    //float price = linePrice->text().toFloat();
    //std::string word = ui->lineSelect->text().toLocal8Bit().constData();
    //-----------------------------------------------------------------

    getListSelect();
    if(uLoad.base.size()>10) uLoad.makeReservCopy();
    ui->pushEdit->setEnabled(false);
    connect (ui->list, SIGNAL(itemSelectionChanged()), this, SLOT(setEditable()));
    connect (timerSeller, SIGNAL(timeout()), this, SLOT(on_buttonSaller_clicked()));
}

MainWindow::~MainWindow()
{
    delete isQueue;
    delete ui;
}





void MainWindow::on_list_doubleClicked()
{
    timerSeller->stop();
    QString str = ui->list->currentItem()->text().left(6);
    un code = str.toInt();
    Unit_edit * unit = new Unit_edit(code, this);
    unit->show();
    unit->exec();
    uLoad.load();
    this->getListSelect();
    ui->pushEdit->setEnabled(false);
}


void MainWindow::on_pushAdd2_clicked()
{
    timerSeller->stop();
    do{
    Add2 * unit = new Add2(isQueue, this);
    unit->show();
    unit->exec();
    uLoad.load();
    this->getListSelect();
    ui->pushEdit->setEnabled(false);
    ui->list->scrollToBottom();
    }while(*isQueue);
}

void MainWindow::setEditable()
{
    ui->pushEdit->setEnabled(true);
    ui->del->setEnabled(true);
    timerSeller->stop();
    timerSeller->start(wait);
}


void MainWindow::on_pushEdit_clicked()
{
   timerSeller->stop();
    QString str = ui->list->currentItem()->text().left(6);
    un code = str.toInt();
    Unit_edit * unit = new Unit_edit(code, this);
    unit->show();
    unit->exec();
    uLoad.load();
    this->getListSelect();
    ui->pushEdit->setEnabled(false);
}


void MainWindow::on_lineSelect_editingFinished(){}


void MainWindow::on_lineSelect_returnPressed()
{
    this->state = "searsh";
    getListSelect();
}

void MainWindow::on_buttonSaller_clicked()
{
    timerSeller->stop();
    Seller * shop = new Seller(this);
    shop->show();
    shop->exec();
}

void MainWindow::getListSelect()
{

        ui->list->clear();
        QString word = ui->lineSelect->text();
        int size = uLoad.base.size();
        std::vector<Unit>base = uLoad.base;

        if (textbutor.isBarcode(word))
        {
            this->state = "searsh";
            QString text = "Поиск по штрих-коду: " + word;
            ui->labelContent->setText(text);
            ui->buttonRefresh->setEnabled(true);
            for(int n=0; n<size; n++)
            {
                QString code = QString::number(base[n].getCode());
                QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),40);
                QString price = textbutor.cutter(QString::number(base[n].getPrice()),10);
                if(isUah(base[n])) {price = "# " + price;} else {price = "$ " + price;}
                QString quantity = textbutor.cutter(QString::number(base[n].getQuantity()),4)+"шт.";
                QString barcode = QString::fromLocal8Bit((base[n].getBarcode()).c_str());

                if(word == barcode)ui->list->addItem(code+"   "+name+"  "+price+" "+quantity);
            }
        }

        if (word.isEmpty() && state == "normal")
        {
            ui->labelContent->setText("Все товары на складе.");
            ui->buttonRefresh->setEnabled(false);
            for(int n=0; n < size; n++)
            {
                QString code = QString::number(base[n].getCode());
                QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),40);
                QString price = textbutor.cutter(QString::number(base[n].getPrice()),10);
                if(isUah(base[n])) {price = "# " + price;} else {price = "$ " + price;}
                QString quantity = textbutor.cutter(QString::number(base[n].getQuantity()),4)+"шт.";
                ui->list->addItem(code+"   "+name+"   "+price+" "+quantity);
            }
            ui->list->scrollToBottom();
        }

        if (!word.isEmpty() && !textbutor.isBarcode(word))
        {
            this->state = "searsh";
            QString text = "Результаты поиска: " + word;
            ui->labelContent->setText(text);
            ui->buttonRefresh->setEnabled(true);
            searsh(word);
            if(ui->list->count() == 0)
            {
                qDebug()<<"change";
                ui->lineSelect->setText(textbutor.latinToKiril(word));
                searsh(textbutor.latinToKiril(word));
            }
            ui->list->scrollToTop();
        }

        if(this->state == "order")
        {
            for(int n=1; n<size; n++)
            {
                int minimum = base[n].getMinimum();
                int quantityInt = base[n].getQuantity();
                QString code = QString::number(base[n].getCode());
                QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),40);
                QString price = textbutor.cutter(QString::number(base[n].getPrice()),7);
                if(isUah(base[n])) {price = "# " + price;} else {price = "$ " + price;}
                QString quantity = textbutor.cutter(QString::number(base[n].getQuantity()),4)+"шт.";
                if (quantityInt < minimum)
                {
                    ui->list->addItem(code+"   "+name+"  "+price+" "+quantity);
                }
            }
        }


        ui->pushEdit->setEnabled(false);
        ui->del->setEnabled(false);
}

void MainWindow::on_del_clicked()
{
    if(!ui->list->currentItem()->text().isEmpty())
    {
        unsigned code = ui->list->currentItem()->text().left(6).toInt();
        Unit unit = uLoad.getUnit(code);
        QString msg;
        msg = "Удалить " + QString::fromLocal8Bit((unit.getName()).c_str()) + "?";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Удаление товара");
        msgBox.setText(msg);
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes)
        {
            uLoad.del(code);
            getListSelect();
        }
    }
}

void MainWindow::on_buttonOrder_clicked()
{
    this->state = "order";
    ui->list->clear();
    ui->labelContent->setText("Заказать товары...");
    ui->buttonRefresh->setEnabled(true);

    getListSelect();
    ui->pushEdit->setEnabled(false);
    ui->del->setEnabled(false);

}

void MainWindow::on_buttonRefresh_clicked()
{
    this->state = "normal";
    ui->lineSelect->clear();
    getListSelect();
}

void MainWindow::on_buttonCustomers_clicked()
{
    timerSeller->stop();
    Customers * box = new Customers(this);
    box->show();
    box->exec();
}

void MainWindow::searsh(QString word)
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

            if (coincidence==(n+1))
            {
                QString code = QString::number(vBase[i].getCode());
                QString name = textbutor.cutter(QString::fromLocal8Bit((vBase[i].getName()).c_str()),40);
                QString price = textbutor.cutter(QString::number(vBase[i].getPrice()),9);
                if(isUah(vBase[i])) {price = "# " + price;} else {price = "$ " + price;}
                QString quantity = textbutor.cutter(QString::number(vBase[i].getQuantity()),4)+"шт.";
                ui->list->addItem(code+"   "+name+"  "+price+" "+quantity);
                vBase.erase(vBase.begin()+i);
                i--;
            }
        }

    }
}

bool MainWindow::isUah(Unit unit)
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



void MainWindow::on_statistica_clicked()
{

    ui->list->clear();

    this->state = "statistica";
    ui->labelContent->setText("Статистика");
    ui->buttonRefresh->setEnabled(true);

    QStringList files = uLoad.getFiles("LOG");
    un length = files.length();
    for(un n = 0; n < length; n++)
    {
        QString info = files[n];
        if (info.right(3)=="log")
        {
            float balance = uLoad.daySummFromLog(info);
            info = info.mid(4, info.size());
            info.chop(4);
            info = textbutor.cutter(info, 12)+ QString::number(balance) + " грн.";
            ui->list->addItem(info);
        }
    }
    ui->list->scrollToTop();
}
