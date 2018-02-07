#include "dialogwindow.h"
#include "ui_dialogwindow.h"

DialogWindow::DialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWindow)
{
    ui->setupUi(this);
    ui->okButton->setDisabled(true);
     ui->groupBox_2->setVisible(false);

    QRegExp exp("[a-zA-Zа-яА-Я0-9$ -.,]{1,30}");
    ui->lineEdit->setValidator(new QRegExpValidator(exp, this));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(okEnabled()));

}

DialogWindow::~DialogWindow()
{
    delete ui;
}


void DialogWindow::okEnabled()
{
    ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput());

}

void DialogWindow::on_pushButton_clicked()
{
    if(ui->pushButton->text()=="More")
        {ui->pushButton->setText("Less");}
    else
        {ui->pushButton->setText("More");}

    static bool open = true;
    ui->groupBox_2->setVisible(open);
    if (open){this->setFixedHeight(215);}
        else {this->setFixedHeight(125);}
    open = !open;
}

void DialogWindow::on_okButton_2_clicked()
{
    ui->lineEdit_2->setText("Hello! Do you know the way???");
}

void DialogWindow::on_closeButton_2_clicked()
{
    //this->close();
}

void DialogWindow::on_okButton_clicked()
{
    const QString a = ui->okButton->text();
    const QString txt = ui->lineEdit->text();
    if(a=="I want 100$" && txt!="This is 100$")
    {
        ui->lineEdit->setText("This is 100$");
        ui->okButton->setText("I is no 100$ !!!");
    }
    if(a=="&Ok") ui->okButton->setText("I want 100$");
    if(a=="I is no 100$ !!!")
    {
        ui->label->setText("");
        ui->lineEdit->setFixedWidth(300);
        ui->lineEdit->setText("Trust me Joshi! Copy this 100$ and put in your pocket.");

    }
}
