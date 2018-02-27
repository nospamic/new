#include "add2.h"
#include "loader.h"

Add2::Add2(QWidget *parent)
    : QDialog(parent)
{
    QFont font("Lucida Console",12);
    this->setFont(font);

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

    QHBoxLayout * hor2 = new QHBoxLayout;
    lineBarcode = new QLineEdit;
    lineBarcode->setPlaceholderText("Штрихкод..");
    buttonGen = new QPushButton("Сгенерировать");
    hor2->addWidget(lineBarcode);
    hor2->addWidget(buttonGen);
    vert->addLayout(hor2);


    ok = new QPushButton("Add");
    vert->addWidget(ok);
    //this->show();
    setLayout(vert);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));
    connect(checkUah, SIGNAL(clicked(bool)), this, SLOT(currencySwich()));
    connect(buttonGen, SIGNAL(clicked(bool)), this, SLOT(setBarcode()));
}

Add2::~Add2()
{

}


void Add2::itsOk()
{
    Loader loader;
    std::string name = lineName->text().toLocal8Bit().constData();
    name = loader.removeSpaces(name);
    std::string barcode = lineBarcode->text().toLocal8Bit().constData();
    if(barcode.length()<12) barcode = "0000000000000";
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
        loader.addUnitToFile(name, price, quantity, barcode, stdDescription);
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

void Add2::setBarcode()
{
    if(lineBarcode->text().isEmpty())
    {
        lineBarcode->setText(textbutor.makeBarcode(loader.getLastCode()+1));
    }
}
