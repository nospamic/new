#ifndef HUMANEDIT_H
#define HUMANEDIT_H

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
#include "humanloader.h"

class HumanEdit : public QDialog
{
    Q_OBJECT

public:
    HumanEdit(unsigned code, QWidget *parent = 0);
    ~HumanEdit();

private:
    unsigned code;

    std::string name;
    std::string tel;
    std::string description;
    float debt;
    float summ;
    int discount;
    HumanLoader humanloader;


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



    void getFields();



public slots:
    void itsOk();

};

#endif // HUMANEDIT_H
