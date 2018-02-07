#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QDialog>

namespace Ui {
class DialogWindow;
}

class DialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWindow(QWidget *parent = 0);
    ~DialogWindow();

private:
    Ui::DialogWindow *ui;
private slots:
    void okEnabled();

    void on_pushButton_clicked();
    void on_okButton_2_clicked();
    void on_closeButton_2_clicked();
    void on_okButton_clicked();
};

#endif // DIALOGWINDOW_H
