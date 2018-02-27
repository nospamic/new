#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QString cPath= "Current path - " + QDir::currentPath();
    std::cout<<cPath.toLocal8Bit().constData()<<"\n";

    QFont font("Lucida Console",10);
    this->setFont(font);


    if(!loader.fileExists())
    {
        QMessageBox msg;
        msg.setText("Файл data.txt не существует. Создаю новый.");
        msg.exec();
        loader.makeNewDateFile(1);
    }
    //------------------------------------------------------------------
    //QString qa=QString::fromStdString(a);
    //QString s = QString::number(i);
    // QString name=QString::fromLocal8Bit((str).c_str());
    //float price = linePrice->text().toFloat();
    //std::string word = ui->lineSelect->text().toLocal8Bit().constData();
    //-----------------------------------------------------------------

    getListSelect();
    //getUnitList();
    ui->pushEdit->setEnabled(false);
    connect (ui->list, SIGNAL(itemSelectionChanged()), this, SLOT(setEditable()));
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_list_doubleClicked()
{
    QString str = ui->list->currentItem()->text().left(6);
    un code = str.toInt();
    EditForm * unit = new EditForm(code);
    unit->show();
    unit->exec();
    this->getListSelect();
    ui->pushEdit->setEnabled(false);
}


void MainWindow::on_pushAdd2_clicked()
{

    Add2 * unit = new Add2;
    unit->show();
    unit->exec();
    this->getListSelect();
    ui->pushEdit->setEnabled(false);
}

void MainWindow::setEditable()
{
    ui->pushEdit->setEnabled(true);
}


void MainWindow::on_pushEdit_clicked()
{
    QString str = ui->list->currentItem()->text().left(6);
    un code = str.toInt();
    EditForm * unit = new EditForm(code);
    unit->show();
    unit->exec();
    this->getListSelect();
    ui->pushEdit->setEnabled(false);
}


void MainWindow::on_lineSelect_editingFinished(){}


void MainWindow::on_lineSelect_returnPressed()
{
    getListSelect();
}

void MainWindow::on_buttonSaller_clicked()
{
    Seller * shop = new Seller;
    shop->show();
    shop->exec();
}

void MainWindow::getListSelect()
{

        ui->list->clear();
        QString word = ui->lineSelect->text();
        int size = loader.objQuantity();
        Unit *base = loader.fileToArr();

        if (word.isEmpty())
        {
            for(int n=1; n<size; n++)
            {
                QString code = QString::number(base[n].getCode());
                QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),30);
                QString price = QString::number(base[n].getPrice());
                QString quantity = QString::number(base[n].getQuantity());
                ui->list->addItem(code+"   "+name+" "+price+"\t   "+quantity);
            }
        }
        else
        {
            word = word.toLower();
            for(int n=0; n<size; n++)
            {
                QString code = QString::number(base[n].getCode());
                QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),30);
                QString price = textbutor.cutter(QString::number(base[n].getPrice()),7);
                QString quantity = QString::number(base[n].getQuantity());
                if (name.contains(word, Qt::CaseInsensitive))
                {
                    ui->list->addItem(code+"   "+name+" "+price+" "+quantity);
                }
            }

        }
        delete[] base;

}

void MainWindow::on_pushButton_clicked()
{
    if(!ui->list->currentItem()->text().isEmpty())
    {
        unsigned code = ui->list->currentItem()->text().left(6).toInt();
        loader.delUnit(code);
        getListSelect();
    }
}
