#ifndef ADD_H
#define ADD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>


class Add : QDialog
{
    Q_OBJECT
public:
    Add(QWidget * parent=0);

private:

    QLineEdit * lineName;
    QLineEdit * linePrice;
    QSpinBox * spinQuant;
    QPushButton * ok;

public slots:
    void itsOk();
};

#endif // ADD_H
