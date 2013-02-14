#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>

namespace Ui {
    class TestDialog;
}

class TestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestDialog(QWidget *parent = 0);
    ~TestDialog();

private:
    Ui::TestDialog *ui;

private slots:
    void startTests();
    void testCompleted();
};

#endif // TESTDIALOG_H
