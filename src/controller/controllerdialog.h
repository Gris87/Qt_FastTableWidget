#ifndef CONTROLLERDIALOG_H
#define CONTROLLERDIALOG_H

#include <QDialog>
#include "ui_controllerdialog.h"

#include <QInputDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QMenu>
#include "qdebug.h"

#include "viewdialog.h"
#include "aligndialog.h"
#include "../fasttable/fasttablewidget.h"
#include "../tests/publictablewidget.h"

namespace Ui {
    class ControllerDialog;
}

class ControllerDialog : public QDialog
{
    Q_OBJECT

public:
    CustomFastTableWidget* mFastTableWidget;

    explicit ControllerDialog(QWidget *parent = 0);
    ~ControllerDialog();

    void setStyleButtonsFlat();

private slots:
    void tableInsertRow();
    void tableDeleteRow();
    void tableInsertColumn();
    void tableDeleteColumn();
    void tableMergeCells();
    void tableContextMenuRequested(QPoint pos);

    void on_deleteButton_clicked();
    void on_styleSimpleButton_clicked();
    void on_styleLinuxButton_clicked();
    void on_styleWinXPButton_clicked();
    void on_styleWin7Button_clicked();

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
    void on_alternatingRowColorsCheckBox_toggled(bool checked);
    void on_selectRowButton_clicked();
    void on_unselectRowButton_clicked();
    void on_selectColumnButton_clicked();
    void on_unselectColumnButton_clicked();
    void on_selectAllButton_clicked();
    void on_unselectAllButton_clicked();
    void on_windowColorButton_clicked();
    void on_defaultBackgroundButton_clicked();
    void on_alternateBackgroundButton_clicked();
    void on_defaultForegroundButton_clicked();
    void on_gridColorButton_clicked();
    void on_cellBorderColorButton_clicked();
    void on_horizontalDefaultBackgroundButton_clicked();
    void on_horizontalDefaultForegroundButton_clicked();
    void on_horizontalGridColorButton_clicked();
    void on_horizontalCellBorderColorButton_clicked();
    void on_verticalDefaultBackgroundButton_clicked();
    void on_verticalDefaultForegroundButton_clicked();
    void on_verticalGridColorButton_clicked();
    void on_verticalCellBorderColorButton_clicked();
    void on_selectionColorButton_clicked();
    void on_selectionTextColorButton_clicked();
    void on_defaultWidthSpinBox_valueChanged(int value);
    void on_defaultHeightSpinBox_valueChanged(int value);
    void on_columnWidthButton_clicked();
    void on_rowHeightButton_clicked();
    void on_headerColumnWidthButton_clicked();
    void on_headerRowHeightButton_clicked();
    void on_showColumnButton_clicked();
    void on_hideColumnButton_clicked();
    void on_showRowButton_clicked();
    void on_hideRowButton_clicked();
    void on_headerShowColumnButton_clicked();
    void on_headerHideColumnButton_clicked();
    void on_headerShowRowButton_clicked();
    void on_headerHideRowButton_clicked();
    void on_scrollToCellButton_clicked();
    void on_scrollToCurrentCellButton_clicked();
    void on_scrollToTopButton_clicked();
    void on_scrollToBottomButton_clicked();
    void on_textButton_clicked();
    void on_horizontalTextButton_clicked();
    void on_verticalTextButton_clicked();
    void on_cellSelectedButton_clicked();
    void on_currentCellButton_clicked();

    void on_backgroundButton_clicked();
    void on_resetBackgroundButton_clicked();
    void on_resetAllBackgroundButton_clicked();
    void on_foregroundButton_clicked();
    void on_resetForegroundButton_clicked();
    void on_resetAllForegroundButton_clicked();
    void on_cellFontButton_clicked();
    void on_resetCellFontButton_clicked();
    void on_resetAllCellFontButton_clicked();
    void on_cellTextFlagsButton_clicked();
    void on_resetCellTextFlagsButton_clicked();
    void on_resetAllCellTextFlagsButton_clicked();
    void on_horizontalBackgroundButton_clicked();
    void on_horizontalResetBackgroundButton_clicked();
    void on_horizontalResetAllBackgroundButton_clicked();
    void on_horizontalForegroundButton_clicked();
    void on_horizontalResetForegroundButton_clicked();
    void on_horizontalResetAllForegroundButton_clicked();
    void on_horizontalCellFontButton_clicked();
    void on_horizontalResetCellFontButton_clicked();
    void on_horizontalResetAllCellFontButton_clicked();
    void on_horizontalCellTextFlagsButton_clicked();
    void on_horizontalResetCellTextFlagsButton_clicked();
    void on_horizontalResetAllCellTextFlagsButton_clicked();
    void on_verticalBackgroundButton_clicked();
    void on_verticalResetBackgroundButton_clicked();
    void on_verticalResetAllBackgroundButton_clicked();
    void on_verticalForegroundButton_clicked();
    void on_verticalResetForegroundButton_clicked();
    void on_verticalResetAllForegroundButton_clicked();
    void on_verticalCellFontButton_clicked();
    void on_verticalResetCellFontButton_clicked();
    void on_verticalResetAllCellFontButton_clicked();
    void on_verticalCellTextFlagsButton_clicked();
    void on_verticalResetCellTextFlagsButton_clicked();
    void on_verticalResetAllCellTextFlagsButton_clicked();
    void on_mergeButton_clicked();
    void on_clearSpansButton_clicked();
    void on_horizontalMergeButton_clicked();
    void on_horizontalClearSpansButton_clicked();
    void on_verticalMergeButton_clicked();
    void on_verticalClearSpansButton_clicked();

    //------------------------------------------------------------------------

    void on_rowCountViewButton_clicked();
    void on_columnCountViewButton_clicked();
    void on_horizontalHeaderRowCountViewButton_clicked();
    void on_verticalHeaderColumnCountViewButton_clicked();
    void on_defaultWidthViewButton_clicked();
    void on_defaultHeightViewButton_clicked();
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
    void on_columnVisibleViewButton_clicked();
    void on_rowVisibleViewButton_clicked();
    void on_headerColumnVisibleViewButton_clicked();
    void on_headerRowVisibleViewButton_clicked();
    void on_textViewButton_clicked();
    void on_horizontalTextViewButton_clicked();
    void on_verticalTextViewButton_clicked();
    void on_cellSelectedViewButton_clicked();
    void on_selectedCellsViewButton_clicked();
    void on_selectedRangesViewButton_clicked();
    void on_topLeftSelectedCellViewButton_clicked();
    void on_rowsSelectedViewButton_clicked();
    void on_columnsSelectedViewButton_clicked();
    void on_currentCellViewButton_clicked();
    void on_lastXViewButton_clicked();
    void on_lastYViewButton_clicked();
    void on_mouseXForShiftViewButton_clicked();
    void on_mouseYForShiftViewButton_clicked();
    void on_mouseResizeLineXViewButton_clicked();
    void on_mouseResizeLineYViewButton_clicked();
    void on_mouseResizeCellViewButton_clicked();
    void on_mousePressedViewButton_clicked();
    void on_ctrlPressedViewButton_clicked();
    void on_shiftPressedViewButton_clicked();
    void on_mouseLocationViewButton_clicked();
    void on_mouseLocationForShiftViewButton_clicked();
    void on_mouseSelectedCellsViewButton_clicked();

    void on_mergeParentViewButton_clicked();
    void on_mergeXYViewButton_clicked();
    void on_mergesViewButton_clicked();
    void on_horizontalMergeParentViewButton_clicked();
    void on_horizontalMergeXYViewButton_clicked();
    void on_horizontalMergesViewButton_clicked();
    void on_verticalMergeParentViewButton_clicked();
    void on_verticalMergeXYViewButton_clicked();
    void on_verticalMergesViewButton_clicked();

    //------------------------------------------------------------------------

    void on_createCustomTableButton_clicked();
    void on_createFastTableButton_clicked();

private:
    Ui::ControllerDialog *ui;
};

#endif // CONTROLLERDIALOG_H
