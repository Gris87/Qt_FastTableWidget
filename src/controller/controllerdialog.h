#ifndef CONTROLLERDIALOG_H
#define CONTROLLERDIALOG_H

#include <QDialog>
#include "ui_controllerdialog.h"

#include "qdebug.h"

#include "src/fasttable/fasttablewidget.h"

namespace Ui {
    class ControllerDialog;
}

class ControllerDialog : public QDialog
{
    Q_OBJECT

public:
    FastTableWidget* mFastTableWidget;

    explicit ControllerDialog(QWidget *parent = 0);
    ~ControllerDialog();

private slots:
    void on_rowCountSpinBox_valueChanged(int value);
    void on_columnCountSpinBox_valueChanged(int value);
    void on_horizontalHeaderRowCountSpinBox_valueChanged(int value);
    void on_verticalHeaderColumnCountSpinBox_valueChanged(int value);

private:
    Ui::ControllerDialog *ui;
};

#endif // CONTROLLERDIALOG_H
