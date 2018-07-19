#include "add2.h"


Add2::Add2(bool *isQueue, QWidget *parent)
    : QDialog(parent)
{
    this->isQueue = isQueue;
    QFont font("Lucida Console",12);
    QFont small("Lucida Console",9);
    QFont big("Lucida Console",14);

    QRegExp money("[0-9]{1,4}[.,]{0,1}[0-9]{0,2}");
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
    linePrice->setFixedWidth(200);
    linePrice->setValidator(new QRegExpValidator(money, this));
    linePrice->setPlaceholderText("Цена (USD)");
    checkUah = new QCheckBox("- цена в грн.");
    hor->addWidget(linePrice);
    hor->addWidget(checkUah);
    vert->addLayout(hor);

    QHBoxLayout * hor1 = new QHBoxLayout;
    QLabel * lab1 = new QLabel("- количество");
    spinQuant = new QSpinBox;
    spinQuant->setFixedWidth(200);
    spinQuant->setMaximum(99999);
    hor1->addWidget(spinQuant);
    hor1->addWidget(lab1);
    vert->addLayout(hor1);

    QHBoxLayout * hor2 = new QHBoxLayout;
    lineBarcode = new QLineEdit;
    lineBarcode->setFixedWidth(200);
    lineBarcode->setValidator(new QRegExpValidator(intager, this));
    lineBarcode->setPlaceholderText("Штрихкод..");
    buttonGen = new QPushButton("Сгенерировать");
    buttonGen->setAutoDefault(false);
    hor2->addWidget(lineBarcode);
    hor2->addWidget(buttonGen);
    vert->addLayout(hor2);

    QFrame *line;
    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    vert->addWidget(line);

    QHBoxLayout * hor4 = new QHBoxLayout;
    checkQueue = new QCheckBox();
    checkQueue->setFont(big);
    checkQueue->setFixedWidth(30);
    checkQueue->setFixedHeight(20);
    hor4->addWidget(checkQueue);
    *isQueue?checkQueue->setChecked(true):checkQueue->setChecked(false);

    ok = new QPushButton("Добавить товар");
    ok->setAutoDefault(false);
    ok->setEnabled(false);
    //ok->setFixedHeight(40);
    hor4->addWidget(ok);

    spinPrint = new QSpinBox;
    spinPrint->setFont(big);
    spinPrint->setFixedWidth(50);
    hor4->addWidget(spinPrint);

    vert->addLayout(hor4);

    QFrame *line1;
    line1 = new QFrame(this);
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    vert->addWidget(line1);

    QHBoxLayout * hor5 = new QHBoxLayout;
    QLabel * lab2 = new QLabel("   <--- Непрерывно");
    lab2->setFont(small);
    QLabel * lab3 = new QLabel("Печатать ценник --->");
    lab3->setFont(small);

    hor5->addWidget(lab2);
    hor5->addWidget(lab3);
    vert->addLayout(hor5);


    setLayout(vert);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));
    connect(checkUah, SIGNAL(clicked(bool)), this, SLOT(currencySwich()));
    connect(buttonGen, SIGNAL(clicked(bool)), this, SLOT(setBarcode()));
    connect(checkQueue, SIGNAL(clicked(bool)), this, SLOT(setQueue(bool)));
    connect(lineName, SIGNAL(textChanged(QString)), this, SLOT(okEnable()));
    connect(linePrice, SIGNAL(textChanged(QString)), this, SLOT(okEnable()));
    connect(lineBarcode, SIGNAL(textChanged(QString)), this, SLOT(okEnable()));
}

Add2::~Add2()
{

}


void Add2::itsOk()
{

    std::string name = lineName->text().toLocal8Bit().constData();
    name = uLoad.removeSpaces(name);
    std::string barcode = lineBarcode->text().toLocal8Bit().constData();
    if(barcode.length()<6) barcode = "0000000000000";
    barcode = uLoad.removeSpaces(barcode);
    int quantity = spinQuant->value();
    float price = textbutor.toDot(linePrice->text()).toFloat();
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
    if(name != "" && uLoad.nameByBarcode(barcode)=="")
    {
        Unit unit;
        unit.setName(name);
        unit.setPrice(price);
        unit.setQuantity(quantity);
        unit.setBarcode(barcode);
        unit.setDescription(stdDescription);
        uLoad.add(unit);
        if(spinPrint->value() > 0)for(int n =0; n<spinPrint->value();n++)printSticker();
        this->close();
    }
    else
    {
        QString message=QString::fromLocal8Bit(uLoad.nameByBarcode(barcode).c_str());
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
        lineBarcode->setText(textbutor.makeBarcode(uLoad.getLastCode()+1));
    }
}

void Add2::setQueue(bool isQ)
{
    *isQueue = isQ;
}

void Add2::printSticker()
{
#ifndef QT_NO_PRINTER
    int yCorrect = -15;
    std::vector<QString>words = textbutor.stringToVector(lineName->text());

    QString upWord = "";
    QString downWord = "";
    if (words.size()>=2)
    {
        upWord = words[0] + " " + words[1];
        if(upWord.size() > 12)
        {
            upWord = words[0];
            for (unsigned n = 1; n < words.size(); n++) {downWord+=words[n]; downWord+=" ";}
        }
        else
        {
            upWord = words[0] + " " + words[1];
            for (unsigned n = 2; n < words.size(); n++) {downWord+=words[n]; downWord+=" ";}
        }
    }
    else
    {
        upWord = words[0];
    }

    //int left = textbutor.spaceFirstPos(lineName->text());

    //int right = lineName->text().size() - left - 1;
    QString Qname = upWord;
    QString QnameRight = textbutor.cutter(downWord, 25);
    QString Qprice = textbutor.makePrice(linePrice->text().toFloat(), checkUah->isChecked() ) + "\n";
    QFont small("Arial Narrow",9);
    QFont big("Arial Narrow", 10);
    //big.setBold(true);
    QFont evan("EanGnivc",32);

    QPrinter printer(QPrinter::HighResolution);
    printer.setPrinterName("sticker");
    printer.setPaperSize(QSizeF(38.0, 23.0), QPrinter::Millimeter);
    printer.setPageMargins(0.0, 0.0, 0.0, 0.0, QPrinter::Millimeter);
    QPainter paint(&printer);
    paint.setPen(Qt::black);
    paint.setFont(small);
    paint.drawText(QRect(10, 20 + yCorrect, 400, 200), Qt::AlignLeft, Qname);
    paint.setFont(big);
    paint.drawText(QRect(210, 20 + yCorrect, 200, 100), Qt::AlignLeft, Qprice);
    paint.setFont(evan);
    paint.drawText(QRect(10, 60 + yCorrect, 400, 200), Qt::AlignLeft, textbutor.barcodeToEvan(lineBarcode->text()));
    paint.setFont(small);
    paint.drawText(QRect(10, 155 + yCorrect, 400, 200), Qt::AlignLeft, QnameRight);

#endif
}

void Add2::okEnable()
{
    if(!lineName->text().isEmpty() && !linePrice->text().isEmpty() && !lineBarcode->text().isEmpty())
    {ok->setEnabled(true);}
}
