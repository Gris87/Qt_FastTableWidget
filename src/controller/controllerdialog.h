#ifndef CONTROLLERDIALOG_H
#define CONTROLLERDIALOG_H

#include <QDialog>
#include "ui_controllerdialog.h"

#include <QInputDialog>
#include <QColorDialog>
#include "qdebug.h"

#include "src/controller/viewdialog.h"
#include "src/fasttable/fasttablewidget.h"
#include "src/tests/publictablewidget.h"

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
    void on_addRowButton_clicked();
    void on_insertRowButton_clicked();
    void on_deleteRowButton_clicked();
    void on_addColumnButton_clicked();
    void on_insertColumnButton_clicked();
    void on_deleteColumnButton_clicked();
    void on_addHeaderRowButton_clicked();
    void on_insertHeaderRowButton_clicked();
    void on_deleteHeaderRowButton_clicked();
    void on_addHeaderColumnButton_clicked();
    void on_insertHeaderColumnButton_clicked();
    void on_deleteHeaderColumnButton_clicked();
    void on_clearButton_clicked();
    void on_selectRowButton_clicked();
    void on_unselectRowButton_clicked();
    void on_selectColumnButton_clicked();
    void on_unselectColumnButton_clicked();
    void on_selectAllButton_clicked();
    void on_unselectAllButton_clicked();
    void on_defaultBackgroundButton_clicked();
    void on_defaultForegroundButton_clicked();
    void on_gridColorButton_clicked();
    void on_horizontalDefaultBackgroundButton_clicked();
    void on_horizontalDefaultForegroundButton_clicked();
    void on_horizontalGridColorButton_clicked();
    void on_verticalDefaultBackgroundButton_clicked();
    void on_verticalDefaultForegroundButton_clicked();
    void on_verticalGridColorButton_clicked();
    void on_selectionColorButton_clicked();
    void on_selectionTextColorButton_clicked();
    void on_defaultWidthSpinBox_valueChanged(int value);
    void on_defaultHeightSpinBox_valueChanged(int value);
    void on_columnWidthButton_clicked();
    void on_rowHeightButton_clicked();
    void on_textButton_clicked();
    void on_horizontalTextButton_clicked();
    void on_verticalTextButton_clicked();
    void on_cellSelectedButton_clicked();

    void on_rowCountViewButton_clicked();
    void on_columnCountViewButton_clicked();
    void on_horizontalHeaderRowCountViewButton_clicked();
    void on_verticalHeaderColumnCountViewButton_clicked();
    void on_defaultWidthViewButton_clicked();
    void on_defaultHeightViewButton_clicked();
    void on_headerColumnWidthButton_clicked();
    void on_headerRowHeightButton_clicked();
    void on_columnWidthViewButton_clicked();
    void on_rowHeightViewButton_clicked();
    void on_headerColumnWidthViewButton_clicked();
    void on_headerRowHeightViewButton_clicked();
    void on_totalWidthViewButton_clicked();
    void on_totalHeightViewButton_clicked();
    void on_headerTotalWidthViewButton_clicked();
    void on_headerTotalHeightViewButton_clicked();
    void on_visibleRangesViewButton_clicked();
    void on_horizontalVisibleRangesViewButton_clicked();
    void on_verticalVisibleRangesViewButton_clicked();
    void on_textViewButton_clicked();
    void on_horizontalTextViewButton_clicked();
    void on_verticalTextViewButton_clicked();
    void on_cellSelectedViewButton_clicked();
    void on_currentSelectionViewButton_clicked();
    void on_rowsSelectedViewButton_clicked();
    void on_columnsSelectedViewButton_clicked();

private:
    Ui::ControllerDialog *ui;
};

#endif // CONTROLLERDIALOG_H
