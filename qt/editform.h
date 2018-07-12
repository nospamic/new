#ifndef EDITFORM_H
#define EDITFORM_H

#include <QValidator>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrinterInfo>
#include <QPainter>
#include "textbutor.h"
#include "loader.h"
#include "unit_loader.h"

class EditForm : public QDialog
{
    Q_OBJECT

public:
    EditForm(unsigned code, QWidget *parent = 0);
    ~EditForm();

private:
    unsigned code;


    QLineEdit * lineName;
    QLineEdit * linePrice;
    QSpinBox * spinQuant;
    QLineEdit * lineBarcode;
    QLineEdit * lineEcharge;
    QLineEdit * lineSection;
    QLineEdit * lineGroup;
    QTextEdit * textDescription;
    QTextEdit * textSticker;
    QSpinBox * spinSales;
    QPushButton * printSticker;



    QPushButton * ok;


    std::string barcode;
    int quantity;
    float price;
    float echarge;
    std::string name;
    std::string section;
    std::string group;
    std::string description;
    unsigned sales;
    bool isUah;
    Textbutor textbutor;
    Loader loader;
    Unit_loader uLoad;
    void getFields();
    void barcodeRepair();


public slots:
    void itsOk();
    void printing();
};

#endif // EDITFORM_H
