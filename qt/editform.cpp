#include "editform.h"
#include "loader.h"
#include "unit.h"

EditForm::EditForm(unsigned code, QWidget *parent)
    : QDialog(parent)
{
    QFont font("Lucida Console",12);
    QFont small("Arial Narrow",10);
    QFont evan("EanGnivc",34);
    QRegExp money("[0-9]{1,4}[.,]{0,1}[0-9]{0,2}");
    QRegExp intager("[0-9]{0,14}");
    this->setFont(font);
    this->setWindowTitle("Редактировать товар");

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
    spinQuant->setMaximum(99999);
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
    lineBarcode->setText(qBarcode);
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

    Unit unit = uLoad.getUnit(code);

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
    name = uLoad.removeSpaces(name);

    int quantity = spinQuant->value();

    float price = textbutor.toDot(linePrice->text()).toFloat();

    std::string barcode = lineBarcode->text().toLocal8Bit().constData();
    if (barcode=="") barcode = this->barcode;
    barcode = uLoad.removeSpaces(barcode);

    float echarge = textbutor.toDot(lineEcharge->text()).toFloat();

    std::string section = lineSection->text().toLocal8Bit().constData();
    if (section=="") section = this->section;
    section = uLoad.removeSpaces(section);

    std::string group = lineGroup->text().toLocal8Bit().constData();
    if (group=="") group = this->group;
    group = uLoad.removeSpaces(group);

    QString descr = textDescription->toPlainText();
    std::string description = descr.toLocal8Bit().constData();
    if (description=="") description = this->description;
    description = uLoad.removeSpaces(description);

    un sales = spinSales->value();

    if(uLoad.getUnit(barcode).getCode() == code || !uLoad.unitExists(barcode))
    {
        Unit unit;
        unit.setCode(code);
        unit.setBarcode(barcode);
        unit.setQuantity(quantity);
        unit.setPrice(price);
        unit.setEcharge(echarge);
        unit.setName(name);
        unit.setSection(section);
        unit.setGroup(group);
        unit.setDescription(description);
        unit.setSalesPerMonth(sales);

        uLoad.edit(unit);
        this->close();
    }
    else
    {
        QString message=QString::fromLocal8Bit(uLoad.nameByBarcode(barcode).c_str());
        QMessageBox msg;
        msg.setText("Товар с таким штрих-кодом уже есть в базе: " + message);
        msg.exec();
    }
}

void EditForm::printing()
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

    QString Qname = upWord;
    QString QnameRight = textbutor.cutter(downWord, 25);

    QString Qprice = textbutor.makePrice(price, isUah) + "\n";
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
//-------------------this works---------------------------------
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
