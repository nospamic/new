#ifndef ADD2_H
#define ADD2_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include "textbutor.h"
#include "loader.h"


class Add2 : public QDialog
{
    Q_OBJECT

public:
    Add2(QWidget *parent = 0);
    ~Add2();
private:

    QLineEdit * lineName;
    QLineEdit * linePrice;
    QLabel *labelUah;
    QCheckBox *checkUah;
    QSpinBox * spinQuant;
    QLineEdit *lineBarcode;
    QPushButton *buttonGen;
    QPushButton * ok;

    Textbutor textbutor;
    Loader loader;

public slots:
    void itsOk();
    void currencySwich();
    void setBarcode();
};

#endif // ADD2_H
