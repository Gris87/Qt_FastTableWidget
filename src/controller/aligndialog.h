#ifndef ALIGNDIALOG_H
#define ALIGNDIALOG_H

#include <QDialog>

namespace Ui {
    class AlignDialog;
}

class AlignDialog : public QDialog
{
    Q_OBJECT

public:
    int resultAlignment;

    explicit AlignDialog(int initAlignment=0, QWidget *parent = 0);
    ~AlignDialog();

private slots:
    void on_topLeftButton_clicked();
    void on_topButton_clicked();
    void on_topRightButton_clicked();
    void on_leftButton_clicked();
    void on_centerButton_clicked();
    void on_rightButton_clicked();
    void on_bottomLeftButton_clicked();
    void on_bottomButton_clicked();
    void on_bottomRightButton_clicked();

private:
    Ui::AlignDialog *ui;
};

#endif // ALIGNDIALOG_H
