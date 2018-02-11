#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QWidget>
#include "loader.h"
#include "unit.h"
#include "add.h"

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

    void on_addUnit_clicked();

    void on_list_doubleClicked(const QModelIndex &index);

    void on_pushAdd2_clicked();



private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

    void getUnitList();

};

#endif // MAINWINDOW_H
