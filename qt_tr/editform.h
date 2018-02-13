#ifndef EDITFORM_H
#define EDITFORM_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTextEdit>

class EditForm : public QDialog
{
    Q_OBJECT

public:
    EditForm(unsigned code,QWidget *parent = 0);
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
    QSpinBox * spinSales;




    QPushButton * ok;

    unsigned barcode;
    int qantity;
    float price;
    float echarge;
    std::string name;
    std::string section;
    std::string group;
    std::string description;
    unsigned sales;

    void getFields();

public slots:
    void itsOk();
};

#endif // EDITFORM_H
