#ifndef SELLER_H
#define SELLER_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QFont>
#include <vector>

#include "loader.h"
#include "unit.h"
#include "textbutor.h"

class Seller : public QDialog
{
    Q_OBJECT

public:
    Seller(QWidget *parent = 0);
    ~Seller();

private:
    QListWidget *listSearsh;
    QLineEdit *lineBarcod;
    QLineEdit *lineSearsh;
    QPushButton *buttonSearsh;
    QListWidget *listCheck;
    QSpinBox *spinQuantity;
    QPushButton *buttonDel;
    QPushButton *buttonPay;
    QLabel *labelSumm;
    QLineEdit *linePay;
    QLabel *labelChange;

    Loader loader;
    Textbutor textbutor;
    char *path;
    std::vector<Unit>check;
    std::vector<int>quantity;
    float exchange;



    void getListSelect(QString word);
    void checkShow();
    bool isUah(Unit unit);

private slots:
    void addToCheck();
    void setSpinQuantity();
    void changeQuantity();
    void barcodeScanned();

};

#endif // SELLER_H
