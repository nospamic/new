/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_data;
    QWidget *centralWidget;
    QLabel *label;
    QListWidget *list;
    QListWidget *listCode;
    QListWidget *listPrice;
    QLabel *label_size;
    QPushButton *pushAdd2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(488, 290);
        actionOpen_data = new QAction(MainWindow);
        actionOpen_data->setObjectName(QStringLiteral("actionOpen_data"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 601, 21));
        list = new QListWidget(centralWidget);
        list->setObjectName(QStringLiteral("list"));
        list->setGeometry(QRect(100, 50, 301, 201));
        listCode = new QListWidget(centralWidget);
        listCode->setObjectName(QStringLiteral("listCode"));
        listCode->setGeometry(QRect(10, 50, 81, 201));
        listPrice = new QListWidget(centralWidget);
        listPrice->setObjectName(QStringLiteral("listPrice"));
        listPrice->setGeometry(QRect(410, 50, 71, 201));
        label_size = new QLabel(centralWidget);
        label_size->setObjectName(QStringLiteral("label_size"));
        label_size->setGeometry(QRect(10, 20, 151, 16));
        pushAdd2 = new QPushButton(centralWidget);
        pushAdd2->setObjectName(QStringLiteral("pushAdd2"));
        pushAdd2->setGeometry(QRect(10, 260, 75, 23));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_data->setText(QApplication::translate("MainWindow", "Open data..", nullptr));
        label->setText(QApplication::translate("MainWindow", "Path", nullptr));
        label_size->setText(QApplication::translate("MainWindow", "Size", nullptr));
        pushAdd2->setText(QApplication::translate("MainWindow", "Add Unit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
