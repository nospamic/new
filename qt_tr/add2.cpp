#include "add2.h"
#include "loader.h"

Add2::Add2(QWidget *parent)
    : QDialog(parent)
{

    QVBoxLayout * vert = new QVBoxLayout;

    lineName = new QLineEdit;
    lineName->setPlaceholderText("Наименование товара");
    //lineName->setFixedWidth(200);
    vert->addWidget(lineName);

    QHBoxLayout *hor = new QHBoxLayout;
    linePrice = new QLineEdit;
    linePrice->setPlaceholderText("Цена (USD)");
    checkUah = new QCheckBox("- цена в грн.");
    hor->addWidget(linePrice);
    hor->addWidget(checkUah);
    vert->addLayout(hor);

    QHBoxLayout * hor1 = new QHBoxLayout;
    QLabel * lab1 = new QLabel("- количество");
    spinQuant = new QSpinBox;
    hor1->addWidget(spinQuant);
    hor1->addWidget(lab1);
    vert->addLayout(hor1);

    lineBarcode = new QLineEdit;
    lineBarcode->setPlaceholderText("Штрихкод..");
    vert->addWidget(lineBarcode);

    ok = new QPushButton("Add");
    vert->addWidget(ok);
    //this->show();
    setLayout(vert);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));
    connect(checkUah, SIGNAL(clicked(bool)), this, SLOT(currencySwich()));
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
    QString description;
    if(checkUah->isChecked())
    {
        description = "#";
    }
    else
    {
        description = "no_description";
    }
    std::string stdDescription = description.toLocal8Bit().constData();
    if(name != "" && loader.nameByBarcode(barcode)=="")
    {
        loader.addUnitToFile(path, name, price, quantity, barcode, stdDescription);
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

void Add2::currencySwich()
{
    if(checkUah->isChecked())
    {
        linePrice->setPlaceholderText("Цена (грн.)");
    }
    else
    {
        linePrice->setPlaceholderText("Цена (USD)");
    }
}
