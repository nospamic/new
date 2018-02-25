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




    void checkShow();
    bool isUah(Unit unit);
    void findRepeat();

private slots:
    void addToCheck();
    void setSpinQuantity();
    void changeQuantity();
    void barcodeScanned();
    void getListSelect();
    void sold();

};

#endif // SELLER_H
