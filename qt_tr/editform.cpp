#include "editform.h"
#include "loader.h"
#include "unit.h"

EditForm::EditForm(unsigned code, QWidget *parent)
    : QDialog(parent)
{
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
    lineBarcode->setText(QString::fromLocal8Bit((barcode).c_str()));
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



    ok = new QPushButton("Add");
    vert->addWidget(ok);

    setLayout(vert);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));
}

EditForm::~EditForm()
{

}

void EditForm::getFields()
{
    Loader loader;
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
}


void EditForm::itsOk()
{
    Loader loader;

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

    if(name != "")
    {
        loader.edit(code, barcode, quantity, price, echarge, name, section, group, description, sales);
        this->close();
    }
}
