#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QWidget>
#include <direct.h>
#include "loader.h"
#include "unit.h"
#include "add2.h"
#include "editform.h"

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
    void on_list_currentRowChanged(int currentRow);
    void on_list_doubleClicked(const QModelIndex &index);
    void on_pushAdd2_clicked();
    void setEditable();
    void on_pushEdit_clicked();

    void on_lineSelect_editingFinished();

    void on_lineSelect_returnPressed();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

    void getUnitList();

};

#endif // MAINWINDOW_H
