#include "mainwindow.h"
#include "ui_mainwindow.h"


char*path="date.txt";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QString cPath= "Current path - " + QDir::currentPath();
    ui->label->setText(cPath);

    //------------------------------------------------------------------
    //QString qa=QString::fromStdString(a);
    //QString s = QString::number(i);
    // QString name=QString::fromLocal8Bit((str).c_str());
    //float price = linePrice->text().toFloat();
    //-----------------------------------------------------------------


    getUnitList();

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


    Loader loader;
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
}


void MainWindow::on_pushAdd2_clicked()
{

    Add2 * unit = new Add2;
    unit->show();
    unit->exec();
    this->getUnitList();
}



