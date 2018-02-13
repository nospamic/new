#include "editform.h"
#include "loader.h"
#include "unit.h"

EditForm::EditForm(unsigned code, QWidget *parent)
    : QDialog(parent)
{
    this->code = code;
    getFields();

    QVBoxLayout * vert = new QVBoxLayout;

    lineName = new QLineEdit;
    lineName->setText(QString::fromLocal8Bit((name).c_str()));
    lineName->setPlaceholderText("Наименование товара");
    lineName->setFixedWidth(200);
    vert->addWidget(lineName);

    linePrice = new QLineEdit;
    linePrice->setText(QString::number(price));
    linePrice->setPlaceholderText("Цена (USD)");
    vert->addWidget(linePrice);

    QHBoxLayout * hor1 = new QHBoxLayout;
    QLabel * lab1 = new QLabel("Количество ");
    spinQuant = new QSpinBox;
    spinQuant->setValue(qantity);
    hor1->addWidget(lab1);
    hor1->addWidget(spinQuant);
    vert->addLayout(hor1);

    lineBarcode = new QLineEdit;
    lineBarcode->setText(QString::number(barcode));
    vert->addWidget(lineBarcode);

    ok = new QPushButton("Add");
    vert->addWidget(ok);
    //this->show();
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
    qantity = unit.getQantity();
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
    name = loader.removeSpaces(name);

    int qantity = spinQuant->value();
    float price = linePrice->text().toFloat();
    un barcode=1234567;
    float echarge=1.5;
    std::string section="no_sect";
    std::string group="no_group";
    std::string description="no_dscrpt";
    un sales=1;

    if(name != "")
    {
        loader.edit(code, barcode, qantity, price, echarge, name, section, group, description, sales);
        this->close();
    }
}
