#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    path="data.txt";
    ui->setupUi(this);

    QString cPath= "Current path - " + QDir::currentPath();
    std::cout<<cPath.toLocal8Bit().constData()<<"\n";

    if ( ! QFile::exists(path) )
    {
        QMessageBox msg;
        msg.setText("Файл data.txt не существует. Создаю новый.");
        msg.exec();
        loader.makeNewDateFile(path, 1);
    }
    //------------------------------------------------------------------
    //QString qa=QString::fromStdString(a);
    //QString s = QString::number(i);
    // QString name=QString::fromLocal8Bit((str).c_str());
    //float price = linePrice->text().toFloat();
    //std::string word = ui->lineSelect->text().toLocal8Bit().constData();
    //-----------------------------------------------------------------


    getUnitList();
    ui->pushEdit->setEnabled(false);
    connect (ui->list, SIGNAL(itemSelectionChanged()), this, SLOT(setEditable()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_list_currentRowChanged(int currentRow)
{
    ui->listCode->setCurrentRow(currentRow);
    ui->listPrice->setCurrentRow(currentRow);


}


void MainWindow::getUnitList()
{

    ui->list->clear();
    ui->listCode->clear();
    ui->listPrice->clear();

    un size=loader.objQuantity(path);
    ui->label_size->setText("К-во товаров: " + QString::number(size));
    if(size>0)
    {
        Unit *arry=new Unit[size];
        arry=loader.fileToArr(path);
        for (int n=0; n<size; n++)
        {
            QString id = QString::number(arry[n].getId());
            QString code = QString::number(arry[n].getCode());
            QString name=QString::fromLocal8Bit((arry[n].getName()).c_str());
            QString price = QString::number(arry[n].getPrice());

            ui->list->addItem(name);
            ui->listCode->addItem(code);
            ui->listPrice->addItem(price);
        }
        delete[] arry;
    }

}


void MainWindow::on_list_doubleClicked(const QModelIndex &index)
{
    QString str = ui->listCode->currentItem()->text();
    un code = str.toInt();
    EditForm * unit = new EditForm(code);
    unit->show();
    unit->exec();
    this->getUnitList();
    ui->pushEdit->setEnabled(false);
}


void MainWindow::on_pushAdd2_clicked()
{

    Add2 * unit = new Add2;
    unit->show();
    unit->exec();
    this->getUnitList();
    ui->pushEdit->setEnabled(false);
}

void MainWindow::setEditable()
{
    ui->pushEdit->setEnabled(true);
}


void MainWindow::on_pushEdit_clicked()
{
    QString str = ui->listCode->currentItem()->text();
    un code = str.toInt();
    EditForm * unit = new EditForm(code);
    unit->show();
    unit->exec();
    this->getUnitList();
    ui->pushEdit->setEnabled(false);
}


void MainWindow::on_lineSelect_editingFinished(){}


void MainWindow::on_lineSelect_returnPressed()
{
    ui->list->clear();
    ui->listCode->clear();
    ui->listPrice->clear();


    int size=loader.objQuantity(path);
    std::string word = ui->lineSelect->text().toLocal8Bit().constData();
    std::cout<<"word = "<<word<<"  size = "<<size<<"\n";


    Unit * arry = loader.selectFromFile(word, size);
    ui->lineSelect->clear();

    for (int n=0; n<size; n++)
    {
        QString code = QString::number(arry[n].getCode());
        QString name=QString::fromLocal8Bit((arry[n].getName()).c_str());
        QString price = QString::number(arry[n].getPrice());

        ui->list->addItem(name);
        ui->listCode->addItem(code);
        ui->listPrice->addItem(price);
    }
    delete[] arry;

}

void MainWindow::on_buttonSaller_clicked()
{
    Seller * shop = new Seller;
    shop->show();
    shop->exec();
}
