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


class Add2 : public QDialog
{
    Q_OBJECT

public:
    Add2(QWidget *parent = 0);
    ~Add2();
private:

    QLineEdit * lineName;
    QLineEdit * linePrice;
    QSpinBox * spinQuant;
    QLineEdit *lineBarcode;
    QPushButton * ok;

public slots:
    void itsOk();
};

#endif // ADD2_H
