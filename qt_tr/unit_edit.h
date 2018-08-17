#ifndef UNIT_EDIT_H
#define UNIT_EDIT_H


#include <QDesktopWidget>
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
#include "unit.h"
#include "unit_loader.h"

class Unit_edit : public QDialog
{
    Q_OBJECT

public:
    Unit_edit(unsigned code, QWidget *parent = 0);
    ~Unit_edit();

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
    QSpinBox * spinPrint;



    QPushButton * ok;

    bool isUah;
    Textbutor textbutor;
    Unit_loader uLoad;
    Unit unit;
    void getFields();
    void barcodeRepair();


public slots:
    void itsOk();
    void printing();
};

#endif // UNIT_EDIT_H
