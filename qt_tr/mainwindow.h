#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QWidget>
#include <direct.h>
#include "loader.h"
#include "textbutor.h"
#include "unit.h"
#include "add2.h"
#include "editform.h"
#include "seller.h"

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

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;


    Loader loader;
    Textbutor textbutor;
    char *path;

};

#endif // MAINWINDOW_H
