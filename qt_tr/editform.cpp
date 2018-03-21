#include "editform.h"
#include "loader.h"
#include "unit.h"

EditForm::EditForm(unsigned code, QWidget *parent)
    : QDialog(parent)
{
    QFont font("Lucida Console",12);
    QFont small("Arial Narrow",10);
    QFont evan("EanGnivc",34);
    QRegExp money("[0-9]{1,4}[.]{0,1}[0-9]{0,2}");
    QRegExp intager("[0-9]{0,14}");
    this->setFont(font);

    this->setFixedWidth(400);
    this->code = code;
    if(code < 100000)this->close();
    getFields();



    QVBoxLayout * vert = new QVBoxLayout;

    lineName = new QLineEdit;
    lineName->setText(QString::fromLocal8Bit((name).c_str()));
    lineName->setPlaceholderText("Наименование товара");
    //lineName->setFixedWidth(200);
    vert->addWidget(lineName);

    linePrice = new QLineEdit;
    linePrice->setValidator(new QRegExpValidator(money, this));
    linePrice->setText(QString::number(price));
    linePrice->setPlaceholderText("Цена (USD)");
    vert->addWidget(linePrice);

    QHBoxLayout * hor1 = new QHBoxLayout;
    QLabel * lab1 = new QLabel("Количество ");
    spinQuant = new QSpinBox;
    spinQuant->setValue(quantity);
    hor1->addWidget(lab1);
    hor1->addWidget(spinQuant);
    vert->addLayout(hor1);

    QHBoxLayout * horSales = new QHBoxLayout;
    QLabel * labHor = new QLabel("Минимальный остаток: ");
    spinSales = new QSpinBox;
    spinSales->setValue(sales);
    horSales->addWidget(labHor);
    horSales->addWidget(spinSales);
    vert->addLayout(horSales);

    QHBoxLayout * hor2 = new QHBoxLayout;
    QLabel * lblBar = new QLabel("Barcode: ");
    lineBarcode = new QLineEdit;
    lineBarcode->setValidator(new QRegExpValidator(intager, this));
    QString qBarcode=QString::fromLocal8Bit((barcode).c_str());
    if (qBarcode.size() == 13)
        {lineBarcode->setText(textbutor.testBarcode13(qBarcode));}
    else
        {lineBarcode->setText(qBarcode);}
    hor2->addWidget(lblBar);
    hor2->addWidget(lineBarcode);
    vert->addLayout(hor2);

    QHBoxLayout * hor3 = new QHBoxLayout;
    QLabel * lblEch = new QLabel("Echarge: ");
    lineEcharge = new QLineEdit;
    lineEcharge->setText(QString::number(echarge));
    hor3->addWidget(lblEch);
    hor3->addWidget(lineEcharge);
    vert->addLayout(hor3);

    lineSection = new QLineEdit;
    lineSection->setText(QString::fromLocal8Bit((section).c_str()));
    lineSection->setPlaceholderText("Раздел..");
    vert->addWidget(lineSection);

    lineGroup = new QLineEdit;
    lineGroup->setText(QString::fromLocal8Bit((group).c_str()));
    lineGroup->setPlaceholderText("Группа..");
    vert->addWidget(lineGroup);

    textDescription = new QTextEdit;
    textDescription->setText(QString::fromLocal8Bit((description).c_str()));
    textDescription->setPlaceholderText("Описание ...");
    textDescription->setFixedHeight(80);
    vert->addWidget(textDescription);

    QHBoxLayout * hor4 = new QHBoxLayout;
    textSticker = new QTextEdit;
    hor4->addWidget(textSticker);

    textSticker->setFixedHeight(80);
    textSticker->setFont(small);
    textSticker->setText(textbutor.makeLable(QString::fromLocal8Bit(name.c_str()), price, isUah));
    textSticker->moveCursor( QTextCursor::End );
    QTextCursor cursor( textSticker->textCursor() );
    QTextCharFormat format;
    format.setFont(evan);
    cursor.setCharFormat( format );
    cursor.insertText(textbutor.barcodeToEvan(QString::fromLocal8Bit(barcode.c_str())));

    printSticker = new QPushButton("Распечатать\nценник");
    hor4->addWidget(printSticker);
    vert->addLayout(hor4);



    ok = new QPushButton(" \n Сохранить \n ");
    vert->addWidget(ok);

    setLayout(vert);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));
    connect(printSticker, SIGNAL(clicked(bool)), this, SLOT(printing()));
}

EditForm::~EditForm()
{

}

void EditForm::getFields()
{

    Unit unit = loader.getUnit(code);

    barcode = unit.getBarcode();
    quantity = unit.getQuantity();
    price = unit.getPrice();
    echarge = unit.getEcharge();
    name = unit.getName();
    section = unit.getSection();
    group = unit.getGroup();
    description = unit.getDescription();
    sales = unit.getSalesPerMonth();
    isUah = unit.isUah();
}

void EditForm::barcodeRepair()
{
    if (lineBarcode->text() != textbutor.makeBarcode(code))
    {
        lineBarcode->setText(textbutor.makeBarcode(code));
    }
}


void EditForm::itsOk()
{
    std::string name = lineName->text().toLocal8Bit().constData();
    if (name=="") name = this->name;
    name = loader.removeSpaces(name);

    int quantity = spinQuant->value();

    float price = linePrice->text().toFloat();

    std::string barcode = lineBarcode->text().toLocal8Bit().constData();
    if (barcode=="") barcode = this->barcode;
    barcode = loader.removeSpaces(barcode);

    float echarge = lineEcharge->text().toFloat();

    std::string section = lineSection->text().toLocal8Bit().constData();
    if (section=="") section = this->section;
    section = loader.removeSpaces(section);

    std::string group = lineGroup->text().toLocal8Bit().constData();
    if (group=="") group = this->group;
    group = loader.removeSpaces(group);

    QString descr = textDescription->toPlainText();
    std::string description = descr.toLocal8Bit().constData();
    if (description=="") description = this->description;
    description = loader.removeSpaces(description);

    un sales = spinSales->value();

    if(true)//(loader.nameByBarcode(barcode)==name || loader.nameByBarcode(barcode)=="")
    {
        loader.edit(code, barcode, quantity, price, echarge, name, section, group, description, sales);
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

void EditForm::printing()
{

#ifndef QT_NO_PRINTER
    QString Qname = textbutor.cutter(QString::fromLocal8Bit(name.c_str()), 17);
    QString Qprice = textbutor.makePrice(price, isUah) + "\n";
    QFont small("Arial Narrow",9);
    QFont big("Arial Narrow", 10);
    big.setBold(true);
    QFont evan("EanGnivc",32);
    QPrinter printer(QPrinter::HighResolution);
    QPainter paint(&printer);
    paint.setPen(Qt::black);
    paint.setFont(small);
    paint.drawText(QRect(20, 20, 400, 200), Qt::AlignLeft, Qname);
    paint.setFont(big);
    paint.drawText(QRect(210, 20, 200, 100), Qt::AlignLeft, Qprice);
    paint.setFont(evan);
    paint.drawText(QRect(10, 60, 400, 200), Qt::AlignLeft, textbutor.barcodeToEvan(lineBarcode->text()));

#endif
//-------------------this work---------------------------------
//    QFont evan("EanGnivc",70);
//    QString text = textbutor.barcodeToEvan(lineBarcode->text());
//    QPrinter printer(QPrinter::HighResolution);
//    printer.setFullPage(true);
//    printer.setPageMargins(QMarginsF(2,2,2,2));
//    textSticker->setContentsMargins(0,0,0,0);
//    QTextDocument *doc = new QTextDocument;
//    doc->setPageSize(QSizeF(printer.pageRect().size()));
//    doc->setDefaultFont(evan);
//    doc->setPlainText(text);
//    doc->print(&printer);
//---------------------------------------------------------------


}
