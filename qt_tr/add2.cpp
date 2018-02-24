#include "add2.h"
#include "loader.h"

Add2::Add2(QWidget *parent)
    : QDialog(parent)
{

    QVBoxLayout * vert = new QVBoxLayout;

    lineName = new QLineEdit;
    lineName->setPlaceholderText("Наименование товара");
    lineName->setFixedWidth(200);
    vert->addWidget(lineName);

    linePrice = new QLineEdit;
    linePrice->setPlaceholderText("Цена (USD)");
    vert->addWidget(linePrice);

    QHBoxLayout * hor1 = new QHBoxLayout;
    QLabel * lab1 = new QLabel("Количество ");
    spinQuant = new QSpinBox;
    hor1->addWidget(lab1);
    hor1->addWidget(spinQuant);
    vert->addLayout(hor1);

    lineBarcode = new QLineEdit;
    lineBarcode->setPlaceholderText("Штрихкод..");
    vert->addWidget(lineBarcode);

    ok = new QPushButton("Add");
    vert->addWidget(ok);
    //this->show();
    setLayout(vert);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));
}

Add2::~Add2()
{

}


void Add2::itsOk()
{
    char*path="data.txt";
    Loader loader;
    std::string name = lineName->text().toLocal8Bit().constData();
    name = loader.removeSpaces(name);
    std::string barcode = lineBarcode->text().toLocal8Bit().constData();
    barcode = loader.removeSpaces(barcode);
    int quantity = spinQuant->value();
    float price = linePrice->text().toFloat();
    if(name != "" && loader.nameByBarcode(barcode)=="")
    {
        loader.addUnitToFile(path, name, price, quantity, barcode);
        this->close();
    }
    else
    {
        QString message=QString::fromLocal8Bit(loader.nameByBarcode(barcode).c_str());
        QMessageBox msg;
        msg.setText("Товар с таким кодом уже есть в базе: " + message);
        msg.exec();
    }
}
