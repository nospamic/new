#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QWidget>
#include <direct.h>
#include "textbutor.h"
#include "unit.h"
#include "unit_loader.h"
#include "add2.h"
#include "unit_edit.h"
#include "seller.h"
#include "customers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_list_doubleClicked();
    void on_pushAdd2_clicked();
    void setEditable();
    void on_pushEdit_clicked();
    void on_lineSelect_editingFinished();
    void on_lineSelect_returnPressed();
    void on_buttonSaller_clicked();
    void getListSelect();

    void on_del_clicked();

    void on_buttonOrder_clicked();

    void on_buttonRefresh_clicked();

    void on_buttonCustomers_clicked();

    void searsh(QString word);

    bool isUah(Unit unit);




    void on_statistica_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;



    Unit_loader uLoad;
    Textbutor textbutor;
    char *path;
    bool *isQueue;
    QString state;
    QTimer *timerSeller;
    int wait;

};

#endif // MAINWINDOW_H
