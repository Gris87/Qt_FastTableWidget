#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>
#include "ui_testdialog.h"

#include <QTimer>
#include "qdebug.h"

#include "src/widgets/testframe.h"

namespace Ui {
    class TestDialog;
}

class TestDialog : public QDialog
{
    Q_OBJECT

public:
    Ui::TestDialog *ui;

    explicit TestDialog(QWidget *parent = 0);
    ~TestDialog();

private slots:
    void startTests();
    void testCompleted();
};

#endif // TESTDIALOG_H
