#include "mainwindow.h"
#include <QApplication>
#include "dialogwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogWindow * w = new DialogWindow;
    w->show();

    return a.exec();
}
