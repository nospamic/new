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
    // QString name=QString::fromLocal8Bit((arry[n].getName()).c_str());
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


void MainWindow::on_addUnit_clicked()
{

    Loader loader;
    std::string name = ui->lineNewName->text().toLocal8Bit().constData();
    name = loader.removeSpaces(name);
    int qantity = ui->spinQuant->value();
    float price = ui->lineNewPrice->text().toFloat();
    if(name != "")
    {
        loader.addUnitToFile(path, name, price, qantity);
        getUnitList();
        ui->lineNewName->clear();
        ui->lineNewPrice->clear();
        ui->spinQuant->clear();
    }
}


void MainWindow::getUnitList()
{


    ui->list->clear();
    ui->listCode->clear();
    ui->listPrice->clear();


    Loader loader;
    un size=loader.objQuantity(path);
    ui->label_size->setText("К-во товаров" + QString::number(size));
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
    QMessageBox msg;
    msg.setText("Yes it is some unit");
    msg.exec();
}

void MainWindow::on_pushAdd2_clicked()
{
   //AddUnit * unit = new AddUnit;
    Add * unit = new Add(0);
    //unit->show();


}



