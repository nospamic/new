#include "add2.h"
#include "loader.h"

Add2::Add2(bool *isQueue, QWidget *parent)
    : QDialog(parent)
{
    this->isQueue = isQueue;
    QFont font("Lucida Console",12);
    QFont small("Lucida Console",9);
    QRegExp money("[0-9]{1,4}[.]{0,1}[0-9]{0,2}");
    QRegExp intager("[0-9]{0,14}");
    this->setFont(font);
    this->setWindowTitle("Добавить новый товар");
    QVBoxLayout * vert = new QVBoxLayout;

    lineName = new QLineEdit;
    lineName->setPlaceholderText("Наименование товара");
    //lineName->setFixedWidth(200);
    vert->addWidget(lineName);

    QHBoxLayout *hor = new QHBoxLayout;
    linePrice = new QLineEdit;
    linePrice->setValidator(new QRegExpValidator(money, this));
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
    lineBarcode->setValidator(new QRegExpValidator(intager, this));
    lineBarcode->setPlaceholderText("Штрихкод..");
    buttonGen = new QPushButton("Сгенерировать");
    hor2->addWidget(lineBarcode);
    hor2->addWidget(buttonGen);
    vert->addLayout(hor2);



    ok = new QPushButton("Добавить товар");
    vert->addWidget(ok);
    checkQueue = new QCheckBox("- добавить несколько товаров подряд");
    checkQueue->setFont(small);
    vert->addWidget(checkQueue);
    *isQueue?checkQueue->setChecked(true):checkQueue->setChecked(false);


    setLayout(vert);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));
    connect(checkUah, SIGNAL(clicked(bool)), this, SLOT(currencySwich()));
    connect(buttonGen, SIGNAL(clicked(bool)), this, SLOT(setBarcode()));
    connect(checkQueue, SIGNAL(clicked(bool)), this, SLOT(setQueue(bool)));
}

Add2::~Add2()
{

}


void Add2::itsOk()
{

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
        description = "#_"+textbutor.getDate();
    }
    else
    {
        description = "$_"+textbutor.getDate();
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

void Add2::setQueue(bool isQ)
{
    *isQueue = isQ;
}
