#include "controllerdialog.h"

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    on_createFastTableButton_clicked();
}

ControllerDialog::~ControllerDialog()
{
    delete ui;
}

void ControllerDialog::on_deleteButton_clicked()
{
    delete mFastTableWidget;

    ui->mainStackedWidget->setCurrentIndex(1);
}

void ControllerDialog::setStyleButtonsFlat()
{
    ui->styleSimpleButton->setFlat(mFastTableWidget->style()!=CustomFastTableWidget::StyleSimple);
    ui->styleLinuxButton->setFlat (mFastTableWidget->style()!=CustomFastTableWidget::StyleLinux);
    ui->styleWinXPButton->setFlat (mFastTableWidget->style()!=CustomFastTableWidget::StyleWinXP);
    ui->styleWin7Button->setFlat  (mFastTableWidget->style()!=CustomFastTableWidget::StyleWin7);
}

void ControllerDialog::on_styleSimpleButton_clicked()
{
    mFastTableWidget->setStyle(CustomFastTableWidget::StyleSimple);
    setStyleButtonsFlat();
}

void ControllerDialog::on_styleLinuxButton_clicked()
{
    mFastTableWidget->setStyle(CustomFastTableWidget::StyleLinux);
    setStyleButtonsFlat();
}

void ControllerDialog::on_styleWinXPButton_clicked()
{
    mFastTableWidget->setStyle(CustomFastTableWidget::StyleWinXP);
    setStyleButtonsFlat();
}

void ControllerDialog::on_styleWin7Button_clicked()
{
    mFastTableWidget->setStyle(CustomFastTableWidget::StyleWin7);
    setStyleButtonsFlat();
}

void ControllerDialog::on_rowCountSpinBox_valueChanged(int value)
{
    mFastTableWidget->setRowCount(value);
}

void ControllerDialog::on_columnCountSpinBox_valueChanged(int value)
{
    mFastTableWidget->setColumnCount(value);
}

void ControllerDialog::on_horizontalHeaderRowCountSpinBox_valueChanged(int value)
{
    mFastTableWidget->horizontalHeader_SetRowCount(value);
}

void ControllerDialog::on_verticalHeaderColumnCountSpinBox_valueChanged(int value)
{
    mFastTableWidget->verticalHeader_SetColumnCount(value);
}

void ControllerDialog::on_addRowButton_clicked()
{
    mFastTableWidget->addRow();

    ui->rowCountSpinBox->blockSignals(true);
    ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
    ui->rowCountSpinBox->blockSignals(false);
}

void ControllerDialog::on_insertRowButton_clicked()
{
    QInputDialog dialog(this);

    dialog.setWindowTitle("Input row");
    dialog.setIntMinimum(0);
    dialog.setIntMaximum(mFastTableWidget->rowCount());
    dialog.setIntValue(0);

    if (dialog.exec())
    {
        mFastTableWidget->insertRow(dialog.intValue());

        ui->rowCountSpinBox->blockSignals(true);
        ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
        ui->rowCountSpinBox->blockSignals(false);
    }
}

void ControllerDialog::on_deleteRowButton_clicked()
{
    if (mFastTableWidget->rowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Delete row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->removeRow(dialog.intValue());

            ui->rowCountSpinBox->blockSignals(true);
            ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
            ui->rowCountSpinBox->blockSignals(false);
        }
    }
}

void ControllerDialog::on_addColumnButton_clicked()
{
    mFastTableWidget->addColumn();

    ui->columnCountSpinBox->blockSignals(true);
    ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
    ui->columnCountSpinBox->blockSignals(false);
}

void ControllerDialog::on_insertColumnButton_clicked()
{
    QInputDialog dialog(this);

    dialog.setWindowTitle("Input column");
    dialog.setIntMinimum(0);
    dialog.setIntMaximum(mFastTableWidget->columnCount());
    dialog.setIntValue(0);

    if (dialog.exec())
    {
        mFastTableWidget->insertColumn(dialog.intValue());

        ui->columnCountSpinBox->blockSignals(true);
        ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
        ui->columnCountSpinBox->blockSignals(false);
    }
}

void ControllerDialog::on_deleteColumnButton_clicked()
{
    if (mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Delete column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->columnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->removeColumn(dialog.intValue());

            ui->columnCountSpinBox->blockSignals(true);
            ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
            ui->columnCountSpinBox->blockSignals(false);
        }
    }
}

void ControllerDialog::on_addHeaderRowButton_clicked()
{
    mFastTableWidget->horizontalHeader_AddRow();

    ui->horizontalHeaderRowCountSpinBox->blockSignals(true);
    ui->horizontalHeaderRowCountSpinBox->setValue(mFastTableWidget->horizontalHeader_RowCount());
    ui->horizontalHeaderRowCountSpinBox->blockSignals(false);
}

void ControllerDialog::on_insertHeaderRowButton_clicked()
{
    QInputDialog dialog(this);

    dialog.setWindowTitle("Input row");
    dialog.setIntMinimum(0);
    dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount());
    dialog.setIntValue(0);

    if (dialog.exec())
    {
        mFastTableWidget->horizontalHeader_InsertRow(dialog.intValue());

        ui->horizontalHeaderRowCountSpinBox->blockSignals(true);
        ui->horizontalHeaderRowCountSpinBox->setValue(mFastTableWidget->horizontalHeader_RowCount());
        ui->horizontalHeaderRowCountSpinBox->blockSignals(false);
    }
}

void ControllerDialog::on_deleteHeaderRowButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Delete row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->horizontalHeader_RemoveRow(dialog.intValue());

            ui->horizontalHeaderRowCountSpinBox->blockSignals(true);
            ui->horizontalHeaderRowCountSpinBox->setValue(mFastTableWidget->horizontalHeader_RowCount());
            ui->horizontalHeaderRowCountSpinBox->blockSignals(false);
        }
    }
}

void ControllerDialog::on_addHeaderColumnButton_clicked()
{
    mFastTableWidget->verticalHeader_AddColumn();

    ui->verticalHeaderColumnCountSpinBox->blockSignals(true);
    ui->verticalHeaderColumnCountSpinBox->setValue(mFastTableWidget->verticalHeader_ColumnCount());
    ui->verticalHeaderColumnCountSpinBox->blockSignals(false);
}

void ControllerDialog::on_insertHeaderColumnButton_clicked()
{
    QInputDialog dialog(this);

    dialog.setWindowTitle("Input column");
    dialog.setIntMinimum(0);
    dialog.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount());
    dialog.setIntValue(0);

    if (dialog.exec())
    {
        mFastTableWidget->verticalHeader_InsertColumn(dialog.intValue());

        ui->verticalHeaderColumnCountSpinBox->blockSignals(true);
        ui->verticalHeaderColumnCountSpinBox->setValue(mFastTableWidget->verticalHeader_ColumnCount());
        ui->verticalHeaderColumnCountSpinBox->blockSignals(false);
    }
}

void ControllerDialog::on_deleteHeaderColumnButton_clicked()
{
    if (mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Delete column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->verticalHeader_RemoveColumn(dialog.intValue());

            ui->verticalHeaderColumnCountSpinBox->blockSignals(true);
            ui->verticalHeaderColumnCountSpinBox->setValue(mFastTableWidget->verticalHeader_ColumnCount());
            ui->verticalHeaderColumnCountSpinBox->blockSignals(false);
        }
    }
}

void ControllerDialog::on_clearButton_clicked()
{
    mFastTableWidget->clear();

    ui->rowCountSpinBox->blockSignals(true);
    ui->columnCountSpinBox->blockSignals(true);
    ui->horizontalHeaderRowCountSpinBox->blockSignals(true);
    ui->verticalHeaderColumnCountSpinBox->blockSignals(true);

    ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
    ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
    ui->horizontalHeaderRowCountSpinBox->setValue(mFastTableWidget->horizontalHeader_RowCount());
    ui->verticalHeaderColumnCountSpinBox->setValue(mFastTableWidget->verticalHeader_ColumnCount());

    ui->rowCountSpinBox->blockSignals(false);
    ui->columnCountSpinBox->blockSignals(false);
    ui->horizontalHeaderRowCountSpinBox->blockSignals(false);
    ui->verticalHeaderColumnCountSpinBox->blockSignals(false);
}

void ControllerDialog::on_selectRowButton_clicked()
{
    if (mFastTableWidget->rowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->selectRow(dialog.intValue());
        }
    }
}

void ControllerDialog::on_unselectRowButton_clicked()
{
    if (mFastTableWidget->rowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Unselect row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->unselectRow(dialog.intValue());
        }
    }

}

void ControllerDialog::on_selectColumnButton_clicked()
{
    if (mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->columnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->selectColumn(dialog.intValue());
        }
    }
}

void ControllerDialog::on_unselectColumnButton_clicked()
{
    if (mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Unselect column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->columnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->unselectColumn(dialog.intValue());
        }
    }
}

void ControllerDialog::on_selectAllButton_clicked()
{
    mFastTableWidget->selectAll();
}

void ControllerDialog::on_unselectAllButton_clicked()
{
    mFastTableWidget->unselectAll();
}

void ControllerDialog::on_defaultBackgroundButton_clicked()
{
    // TODO: Alternate base
    QPalette aPalette=mFastTableWidget->palette();

    QColorDialog dialog(this);

    dialog.setWindowTitle("Default background color");
    dialog.setCurrentColor(aPalette.color(QPalette::Base));

    if (dialog.exec())
    {
        aPalette.setColor(QPalette::Base, dialog.selectedColor());
        mFastTableWidget->setPalette(aPalette);
    }
}

void ControllerDialog::on_defaultForegroundButton_clicked()
{
    QPalette aPalette=mFastTableWidget->palette();

    QColorDialog dialog(this);

    dialog.setWindowTitle("Default foreground color");
    dialog.setCurrentColor(aPalette.color(QPalette::Text));

    if (dialog.exec())
    {
        aPalette.setColor(QPalette::Text, dialog.selectedColor());
        mFastTableWidget->setPalette(aPalette);
    }
}

void ControllerDialog::on_gridColorButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Grid color");
    dialog.setCurrentColor(mFastTableWidget->gridColor());

    if (dialog.exec())
    {
        mFastTableWidget->setGridColor(dialog.selectedColor());
    }
}

void ControllerDialog::on_cellBorderColorButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Cell border color");
    dialog.setCurrentColor(mFastTableWidget->cellBorderColor());

    if (dialog.exec())
    {
        mFastTableWidget->setCellBorderColor(dialog.selectedColor());
    }
}

void ControllerDialog::on_horizontalDefaultBackgroundButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Default background color");
    dialog.setCurrentColor(mFastTableWidget->horizontalHeader_DefaultBackgroundBrush().color());

    if (dialog.exec())
    {
        mFastTableWidget->horizontalHeader_SetDefaultBackgroundBrush(QBrush(dialog.selectedColor()));
    }
}

void ControllerDialog::on_horizontalDefaultForegroundButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Default foreground color");
    dialog.setCurrentColor(mFastTableWidget->horizontalHeader_DefaultForegroundColor());

    if (dialog.exec())
    {
        mFastTableWidget->horizontalHeader_SetDefaultForegroundColor(dialog.selectedColor());
    }
}

void ControllerDialog::on_horizontalGridColorButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Grid color");
    dialog.setCurrentColor(mFastTableWidget->horizontalHeader_GridColor());

    if (dialog.exec())
    {
        mFastTableWidget->horizontalHeader_SetGridColor(dialog.selectedColor());
    }
}

void ControllerDialog::on_horizontalCellBorderColorButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Cell border color");
    dialog.setCurrentColor(mFastTableWidget->horizontalHeader_CellBorderColor());

    if (dialog.exec())
    {
        mFastTableWidget->horizontalHeader_SetCellBorderColor(dialog.selectedColor());
    }
}

void ControllerDialog::on_verticalDefaultBackgroundButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Default background color");
    dialog.setCurrentColor(mFastTableWidget->verticalHeader_DefaultBackgroundBrush().color());

    if (dialog.exec())
    {
        mFastTableWidget->verticalHeader_SetDefaultBackgroundBrush(QBrush(dialog.selectedColor()));
    }
}

void ControllerDialog::on_verticalDefaultForegroundButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Default foreground color");
    dialog.setCurrentColor(mFastTableWidget->verticalHeader_DefaultForegroundColor());

    if (dialog.exec())
    {
        mFastTableWidget->verticalHeader_SetDefaultForegroundColor(dialog.selectedColor());
    }
}

void ControllerDialog::on_verticalGridColorButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Grid color");
    dialog.setCurrentColor(mFastTableWidget->verticalHeader_GridColor());

    if (dialog.exec())
    {
        mFastTableWidget->verticalHeader_SetGridColor(dialog.selectedColor());
    }
}

void ControllerDialog::on_verticalCellBorderColorButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Cell border color");
    dialog.setCurrentColor(mFastTableWidget->verticalHeader_CellBorderColor());

    if (dialog.exec())
    {
        mFastTableWidget->verticalHeader_SetCellBorderColor(dialog.selectedColor());
    }
}

void ControllerDialog::on_selectionColorButton_clicked()
{
    QPalette aPalette=mFastTableWidget->palette();

    QColorDialog dialog(this);

    dialog.setWindowTitle("Selection color");
    dialog.setCurrentColor(aPalette.color(QPalette::Highlight));

    if (dialog.exec())
    {
        aPalette.setColor(QPalette::Highlight, dialog.selectedColor());
        mFastTableWidget->setPalette(aPalette);
    }
}

void ControllerDialog::on_selectionTextColorButton_clicked()
{
    QPalette aPalette=mFastTableWidget->palette();

    QColorDialog dialog(this);

    dialog.setWindowTitle("Selection text color");
    dialog.setCurrentColor(aPalette.color(QPalette::HighlightedText));

    if (dialog.exec())
    {
        aPalette.setColor(QPalette::HighlightedText, dialog.selectedColor());
        mFastTableWidget->setPalette(aPalette);
    }
}

void ControllerDialog::on_defaultWidthSpinBox_valueChanged(int value)
{
    mFastTableWidget->setDefaultWidth(value);
}

void ControllerDialog::on_defaultHeightSpinBox_valueChanged(int value)
{
    mFastTableWidget->setDefaultHeight(value);
}

void ControllerDialog::on_columnWidthButton_clicked()
{
    if (mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->columnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Input width");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(32767);
            dialog2.setIntValue(mFastTableWidget->columnWidth(dialog.intValue()));

            if (dialog2.exec())
            {
                mFastTableWidget->setColumnWidth(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_rowHeightButton_clicked()
{
    if (mFastTableWidget->rowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Input height");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(32767);
            dialog2.setIntValue(mFastTableWidget->rowHeight(dialog.intValue()));

            if (dialog2.exec())
            {
                mFastTableWidget->setRowHeight(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_headerColumnWidthButton_clicked()
{
    if (mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Input width");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(32767);
            dialog2.setIntValue(mFastTableWidget->verticalHeader_ColumnWidth(dialog.intValue()));

            if (dialog2.exec())
            {
                mFastTableWidget->verticalHeader_SetColumnWidth(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_headerRowHeightButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Input height");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(32767);
            dialog2.setIntValue(mFastTableWidget->horizontalHeader_RowHeight(dialog.intValue()));

            if (dialog2.exec())
            {
                mFastTableWidget->horizontalHeader_SetRowHeight(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_showColumnButton_clicked()
{
    if (mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->columnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->setColumnVisible(dialog.intValue(), true);
        }
    }
}

void ControllerDialog::on_hideColumnButton_clicked()
{
    if (mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->columnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->setColumnVisible(dialog.intValue(), false);
        }
    }
}

void ControllerDialog::on_showRowButton_clicked()
{
    if (mFastTableWidget->rowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->setRowVisible(dialog.intValue(), true);
        }
    }
}

void ControllerDialog::on_hideRowButton_clicked()
{
    if (mFastTableWidget->rowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->setRowVisible(dialog.intValue(), false);
        }
    }
}

void ControllerDialog::on_headerShowColumnButton_clicked()
{
    if (mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->verticalHeader_SetColumnVisible(dialog.intValue(), true);
        }
    }
}

void ControllerDialog::on_headerHideColumnButton_clicked()
{
    if (mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select column");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->verticalHeader_SetColumnVisible(dialog.intValue(), false);
        }
    }
}

void ControllerDialog::on_headerShowRowButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->horizontalHeader_SetRowVisible(dialog.intValue(), true);
        }
    }
}

void ControllerDialog::on_headerHideRowButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            mFastTableWidget->horizontalHeader_SetRowVisible(dialog.intValue(), false);
        }
    }
}

void ControllerDialog::on_scrollToCellButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                mFastTableWidget->scrollToCell(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_scrollToCurrentCellButton_clicked()
{
    mFastTableWidget->scrollToCurrentCell();
}

void ControllerDialog::on_scrollToTopButton_clicked()
{
    mFastTableWidget->scrollToTop();
}

void ControllerDialog::on_scrollToBottomButton_clicked()
{
    mFastTableWidget->scrollToBottom();
}

void ControllerDialog::on_textButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QInputDialog dialog3(this);

                dialog3.setWindowTitle("Input text");
                dialog3.setTextValue(mFastTableWidget->text(dialog.intValue(), dialog2.intValue()));

                if (dialog3.exec())
                {
                    mFastTableWidget->setText(dialog.intValue(), dialog2.intValue(), dialog3.textValue());
                }
            }
        }
    }
}

void ControllerDialog::on_horizontalTextButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QInputDialog dialog3(this);

                dialog3.setWindowTitle("Input text");
                dialog3.setTextValue(mFastTableWidget->horizontalHeader_Text(dialog.intValue(), dialog2.intValue()));

                if (dialog3.exec())
                {
                    mFastTableWidget->horizontalHeader_SetText(dialog.intValue(), dialog2.intValue(), dialog3.textValue());
                }
            }
        }
    }
}

void ControllerDialog::on_verticalTextButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QInputDialog dialog3(this);

                dialog3.setWindowTitle("Input text");
                dialog3.setTextValue(mFastTableWidget->verticalHeader_Text(dialog.intValue(), dialog2.intValue()));

                if (dialog3.exec())
                {
                    mFastTableWidget->verticalHeader_SetText(dialog.intValue(), dialog2.intValue(), dialog3.textValue());
                }
            }
        }
    }
}

void ControllerDialog::on_cellSelectedButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                mFastTableWidget->setCellSelected(dialog.intValue(), dialog2.intValue(), !mFastTableWidget->cellSelected(dialog.intValue(), dialog2.intValue()));
            }
        }
    }
}

void ControllerDialog::on_currentCellButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                mFastTableWidget->setCurrentCell(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_backgroundButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QColorDialog dialog3(this);

                dialog3.setWindowTitle("Background color");
                dialog3.setCurrentColor(((FastTableWidget*)mFastTableWidget)->backgroundBrush(dialog.intValue(), dialog2.intValue()).color());

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->setBackgroundBrush(dialog.intValue(), dialog2.intValue(), QBrush(dialog3.selectedColor()));
                }
            }
        }
    }
}

void ControllerDialog::on_resetBackgroundButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->resetBackgroundBrush(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_resetAllBackgroundButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->resetBackgroundBrushes();
}

void ControllerDialog::on_foregroundButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QColorDialog dialog3(this);

                dialog3.setWindowTitle("Foreground color");
                dialog3.setCurrentColor(((FastTableWidget*)mFastTableWidget)->foregroundColor(dialog.intValue(), dialog2.intValue()));

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->setForegroundColor(dialog.intValue(), dialog2.intValue(), dialog3.selectedColor());
                }
            }
        }
    }
}

void ControllerDialog::on_resetForegroundButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->resetForegroundColor(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_resetAllForegroundButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->resetForegroundColors();
}

void ControllerDialog::on_cellFontButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QFontDialog dialog3(this);

                dialog3.setWindowTitle("Cell font");
                dialog3.setCurrentFont(((FastTableWidget*)mFastTableWidget)->cellFont(dialog.intValue(), dialog2.intValue()));

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->setCellFont(dialog.intValue(), dialog2.intValue(), dialog3.selectedFont());
                }
            }
        }
    }
}

void ControllerDialog::on_resetCellFontButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->resetFont(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_resetAllCellFontButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->resetFonts();
}

void ControllerDialog::on_cellTextFlagsButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                AlignDialog dialog3(((FastTableWidget*)mFastTableWidget)->cellTextFlags(dialog.intValue(), dialog2.intValue()), this);

                dialog3.setWindowTitle("Cell text flags");

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->setCellTextFlags(dialog.intValue(), dialog2.intValue(), dialog3.resultAlignment);
                }
            }
        }
    }
}

void ControllerDialog::on_resetCellTextFlagsButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->resetCellTextFlag(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_resetAllCellTextFlagsButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->resetCellTextFlags();
}

void ControllerDialog::on_horizontalBackgroundButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QColorDialog dialog3(this);

                dialog3.setWindowTitle("Background color");
                dialog3.setCurrentColor(((FastTableWidget*)mFastTableWidget)->horizontalHeader_BackgroundBrush(dialog.intValue(), dialog2.intValue()).color());

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->horizontalHeader_SetBackgroundBrush(dialog.intValue(), dialog2.intValue(), QBrush(dialog3.selectedColor()));
                }
            }
        }
    }
}

void ControllerDialog::on_horizontalResetBackgroundButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->horizontalHeader_ResetBackgroundBrush(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_horizontalResetAllBackgroundButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->horizontalHeader_ResetBackgroundBrushes();
}

void ControllerDialog::on_horizontalForegroundButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QColorDialog dialog3(this);

                dialog3.setWindowTitle("Foreground color");
                dialog3.setCurrentColor(((FastTableWidget*)mFastTableWidget)->horizontalHeader_ForegroundColor(dialog.intValue(), dialog2.intValue()));

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->horizontalHeader_SetForegroundColor(dialog.intValue(), dialog2.intValue(), dialog3.selectedColor());
                }
            }
        }
    }
}

void ControllerDialog::on_horizontalResetForegroundButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->horizontalHeader_ResetForegroundColor(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_horizontalResetAllForegroundButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->horizontalHeader_ResetForegroundColors();
}

void ControllerDialog::on_horizontalCellFontButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QFontDialog dialog3(this);

                dialog3.setWindowTitle("Cell font");
                dialog3.setCurrentFont(((FastTableWidget*)mFastTableWidget)->horizontalHeader_CellFont(dialog.intValue(), dialog2.intValue()));

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->horizontalHeader_SetCellFont(dialog.intValue(), dialog2.intValue(), dialog3.selectedFont());
                }
            }
        }
    }
}

void ControllerDialog::on_horizontalResetCellFontButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->horizontalHeader_ResetFont(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_horizontalResetAllCellFontButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->horizontalHeader_ResetFonts();
}

void ControllerDialog::on_horizontalCellTextFlagsButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                AlignDialog dialog3(((FastTableWidget*)mFastTableWidget)->horizontalHeader_CellTextFlags(dialog.intValue(), dialog2.intValue()), this);

                dialog3.setWindowTitle("Cell text flags");

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->horizontalHeader_SetCellTextFlags(dialog.intValue(), dialog2.intValue(), dialog3.resultAlignment);
                }
            }
        }
    }
}

void ControllerDialog::on_horizontalResetCellTextFlagsButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->horizontalHeader_ResetCellTextFlag(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_horizontalResetAllCellTextFlagsButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->horizontalHeader_ResetCellTextFlags();
}

void ControllerDialog::on_verticalBackgroundButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QColorDialog dialog3(this);

                dialog3.setWindowTitle("Background color");
                dialog3.setCurrentColor(((FastTableWidget*)mFastTableWidget)->verticalHeader_BackgroundBrush(dialog.intValue(), dialog2.intValue()).color());

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->verticalHeader_SetBackgroundBrush(dialog.intValue(), dialog2.intValue(), QBrush(dialog3.selectedColor()));
                }
            }
        }
    }
}

void ControllerDialog::on_verticalResetBackgroundButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->verticalHeader_ResetBackgroundBrush(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_verticalResetAllBackgroundButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->verticalHeader_ResetBackgroundBrushes();
}

void ControllerDialog::on_verticalForegroundButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QColorDialog dialog3(this);

                dialog3.setWindowTitle("Foreground color");
                dialog3.setCurrentColor(((FastTableWidget*)mFastTableWidget)->verticalHeader_ForegroundColor(dialog.intValue(), dialog2.intValue()));

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->verticalHeader_SetForegroundColor(dialog.intValue(), dialog2.intValue(), dialog3.selectedColor());
                }
            }
        }
    }
}

void ControllerDialog::on_verticalResetForegroundButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->verticalHeader_ResetForegroundColor(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_verticalResetAllForegroundButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->verticalHeader_ResetForegroundColors();
}

void ControllerDialog::on_verticalCellFontButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QFontDialog dialog3(this);

                dialog3.setWindowTitle("Cell font");
                dialog3.setCurrentFont(((FastTableWidget*)mFastTableWidget)->verticalHeader_CellFont(dialog.intValue(), dialog2.intValue()));

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->verticalHeader_SetCellFont(dialog.intValue(), dialog2.intValue(), dialog3.selectedFont());
                }
            }
        }
    }
}

void ControllerDialog::on_verticalResetCellFontButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->verticalHeader_ResetFont(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_verticalResetAllCellFontButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->verticalHeader_ResetFonts();
}

void ControllerDialog::on_verticalCellTextFlagsButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                AlignDialog dialog3(((FastTableWidget*)mFastTableWidget)->verticalHeader_CellTextFlags(dialog.intValue(), dialog2.intValue()), this);

                dialog3.setWindowTitle("Cell text flags");

                if (dialog3.exec())
                {
                    ((FastTableWidget*)mFastTableWidget)->verticalHeader_SetCellTextFlags(dialog.intValue(), dialog2.intValue(), dialog3.resultAlignment);
                }
            }
        }
    }
}

void ControllerDialog::on_verticalResetCellTextFlagsButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                ((FastTableWidget*)mFastTableWidget)->verticalHeader_ResetCellTextFlag(dialog.intValue(), dialog2.intValue());
            }
        }
    }
}

void ControllerDialog::on_verticalResetAllCellTextFlagsButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->verticalHeader_ResetCellTextFlags();
}

void ControllerDialog::on_mergeButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QInputDialog dialog3(this);

                dialog3.setWindowTitle("Select row");
                dialog3.setIntMinimum(0);
                dialog3.setIntMaximum(mFastTableWidget->rowCount()-1);
                dialog3.setIntValue(0);

                if (dialog3.exec())
                {
                    QInputDialog dialog4(this);

                    dialog4.setWindowTitle("Select column");
                    dialog4.setIntMinimum(0);
                    dialog4.setIntMaximum(mFastTableWidget->columnCount()-1);
                    dialog4.setIntValue(0);

                    if (dialog4.exec())
                    {
                        int aLeft=qMin(dialog2.intValue(), dialog4.intValue());
                        int aTop=qMin(dialog.intValue(), dialog3.intValue());
                        int aRight=qMax(dialog2.intValue(), dialog4.intValue());
                        int aBottom=qMax(dialog.intValue(), dialog3.intValue());

                        ((FastTableWidget*)mFastTableWidget)->setSpan(aTop, aLeft, aBottom-aTop+1, aRight-aLeft+1);
                    }
                }
            }
        }
    }
}

void ControllerDialog::on_clearSpansButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->clearSpans();
}

void ControllerDialog::on_horizontalMergeButton_clicked()
{
    if (mFastTableWidget->horizontalHeader_RowCount()>0 && mFastTableWidget->columnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->columnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QInputDialog dialog3(this);

                dialog3.setWindowTitle("Select row");
                dialog3.setIntMinimum(0);
                dialog3.setIntMaximum(mFastTableWidget->horizontalHeader_RowCount()-1);
                dialog3.setIntValue(0);

                if (dialog3.exec())
                {
                    QInputDialog dialog4(this);

                    dialog4.setWindowTitle("Select column");
                    dialog4.setIntMinimum(0);
                    dialog4.setIntMaximum(mFastTableWidget->columnCount()-1);
                    dialog4.setIntValue(0);

                    if (dialog4.exec())
                    {
                        int aLeft=qMin(dialog2.intValue(), dialog4.intValue());
                        int aTop=qMin(dialog.intValue(), dialog3.intValue());
                        int aRight=qMax(dialog2.intValue(), dialog4.intValue());
                        int aBottom=qMax(dialog.intValue(), dialog3.intValue());

                        ((FastTableWidget*)mFastTableWidget)->horizontalHeader_SetSpan(aTop, aLeft, aBottom-aTop+1, aRight-aLeft+1);
                    }
                }
            }
        }
    }
}

void ControllerDialog::on_horizontalClearSpansButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->horizontalHeader_ClearSpans();
}

void ControllerDialog::on_verticalMergeButton_clicked()
{
    if (mFastTableWidget->rowCount()>0 && mFastTableWidget->verticalHeader_ColumnCount()>0)
    {
        QInputDialog dialog(this);

        dialog.setWindowTitle("Select row");
        dialog.setIntMinimum(0);
        dialog.setIntMaximum(mFastTableWidget->rowCount()-1);
        dialog.setIntValue(0);

        if (dialog.exec())
        {
            QInputDialog dialog2(this);

            dialog2.setWindowTitle("Select column");
            dialog2.setIntMinimum(0);
            dialog2.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
            dialog2.setIntValue(0);

            if (dialog2.exec())
            {
                QInputDialog dialog3(this);

                dialog3.setWindowTitle("Select row");
                dialog3.setIntMinimum(0);
                dialog3.setIntMaximum(mFastTableWidget->rowCount()-1);
                dialog3.setIntValue(0);

                if (dialog3.exec())
                {
                    QInputDialog dialog4(this);

                    dialog4.setWindowTitle("Select column");
                    dialog4.setIntMinimum(0);
                    dialog4.setIntMaximum(mFastTableWidget->verticalHeader_ColumnCount()-1);
                    dialog4.setIntValue(0);

                    if (dialog4.exec())
                    {
                        int aLeft=qMin(dialog2.intValue(), dialog4.intValue());
                        int aTop=qMin(dialog.intValue(), dialog3.intValue());
                        int aRight=qMax(dialog2.intValue(), dialog4.intValue());
                        int aBottom=qMax(dialog.intValue(), dialog3.intValue());

                        ((FastTableWidget*)mFastTableWidget)->verticalHeader_SetSpan(aTop, aLeft, aBottom-aTop+1, aRight-aLeft+1);
                    }
                }
            }
        }
    }
}

void ControllerDialog::on_verticalClearSpansButton_clicked()
{
    ((FastTableWidget*)mFastTableWidget)->verticalHeader_ClearSpans();
}

void ControllerDialog::on_rowCountViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getRowCount(), this);
    dialog.exec();
}

void ControllerDialog::on_columnCountViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getColumnCount(), this);
    dialog.exec();
}

void ControllerDialog::on_horizontalHeaderRowCountViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->horizontalHeader_GetRowCount(), this);
    dialog.exec();
}

void ControllerDialog::on_verticalHeaderColumnCountViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->verticalHeader_GetColumnCount(), this);
    dialog.exec();
}

void ControllerDialog::on_defaultWidthViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->defaultWidth(), this);
    dialog.exec();
}

void ControllerDialog::on_defaultHeightViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->defaultHeight(), this);
    dialog.exec();
}

void ControllerDialog::on_columnWidthViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getColumnWidths(), false, this);
    dialog.exec();
}

void ControllerDialog::on_rowHeightViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getRowHeights(), true, this);
    dialog.exec();
}

void ControllerDialog::on_headerColumnWidthViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->verticalHeader_GetColumnWidths(), false, this);
    dialog.exec();
}

void ControllerDialog::on_headerRowHeightViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->horizontalHeader_GetRowHeights(), true, this);
    dialog.exec();
}

void ControllerDialog::on_totalWidthViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->totalWidth(), this);
    dialog.exec();
}

void ControllerDialog::on_totalHeightViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->totalHeight(), this);
    dialog.exec();
}

void ControllerDialog::on_headerTotalWidthViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->verticalHeader_TotalWidth(), this);
    dialog.exec();
}

void ControllerDialog::on_headerTotalHeightViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->horizontalHeader_TotalHeight(), this);
    dialog.exec();
}

void ControllerDialog::on_visibleRangesViewButton_clicked()
{
    ViewDialog dialog(mFastTableWidget->visibleRange(), this);
    dialog.exec();
}

void ControllerDialog::on_horizontalVisibleRangesViewButton_clicked()
{
    ViewDialog dialog(mFastTableWidget->horizontalHeader_VisibleRange(), this);
    dialog.exec();
}

void ControllerDialog::on_verticalVisibleRangesViewButton_clicked()
{
    ViewDialog dialog(mFastTableWidget->verticalHeader_VisibleRange(), this);
    dialog.exec();
}

void ControllerDialog::on_columnVisibleViewButton_clicked()
{
    QList<bool> aList;

    for (int i=0; i<mFastTableWidget->columnCount(); ++i)
    {
        aList.append(mFastTableWidget->columnVisible(i));
    }

    ViewDialog dialog(&aList, false, this);
    dialog.exec();
}

void ControllerDialog::on_rowVisibleViewButton_clicked()
{
    QList<bool> aList;

    for (int i=0; i<mFastTableWidget->rowCount(); ++i)
    {
        aList.append(mFastTableWidget->rowVisible(i));
    }

    ViewDialog dialog(&aList, true, this);
    dialog.exec();
}

void ControllerDialog::on_headerColumnVisibleViewButton_clicked()
{
    QList<bool> aList;

    for (int i=0; i<mFastTableWidget->verticalHeader_ColumnCount(); ++i)
    {
        aList.append(mFastTableWidget->verticalHeader_ColumnVisible(i));
    }

    ViewDialog dialog(&aList, false, this);
    dialog.exec();
}

void ControllerDialog::on_headerRowVisibleViewButton_clicked()
{
    QList<bool> aList;

    for (int i=0; i<mFastTableWidget->horizontalHeader_RowCount(); ++i)
    {
        aList.append(mFastTableWidget->horizontalHeader_RowVisible(i));
    }

    ViewDialog dialog(&aList, true, this);
    dialog.exec();
}

void ControllerDialog::on_textViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getData(), this);
    dialog.exec();
}

void ControllerDialog::on_horizontalTextViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->horizontalHeader_GetData(), this);
    dialog.exec();
}

void ControllerDialog::on_verticalTextViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->verticalHeader_GetData(), this);
    dialog.exec();
}

void ControllerDialog::on_cellSelectedViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getSelectedCells(), this);
    dialog.exec();
}

void ControllerDialog::on_selectedCellsViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getCurSelection(), this);
    dialog.exec();
}

void ControllerDialog::on_selectedRangesViewButton_clicked()
{
    QList<QRect> aList=mFastTableWidget->selectedRanges();

    ViewDialog dialog(&aList, this);
    dialog.exec();
}

void ControllerDialog::on_topLeftSelectedCellViewButton_clicked()
{
    ViewDialog dialog(mFastTableWidget->topLeftSelectedCell(), this);
    dialog.exec();
}

void ControllerDialog::on_rowsSelectedViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->verticalHeader_GetSelectedRows(), true, this);
    dialog.exec();
}

void ControllerDialog::on_columnsSelectedViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->horizontalHeader_GetSelectedColumns(), false, this);
    dialog.exec();
}

void ControllerDialog::on_currentCellViewButton_clicked()
{
    ViewDialog dialog(mFastTableWidget->currentCell(), this);
    dialog.exec();
}

void ControllerDialog::on_lastXViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getLastX(), this);
    dialog.exec();
}

void ControllerDialog::on_lastYViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getLastY(), this);
    dialog.exec();
}

void ControllerDialog::on_mouseXForShiftViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getMouseXForShift(), this);
    dialog.exec();
}

void ControllerDialog::on_mouseYForShiftViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getMouseYForShift(), this);
    dialog.exec();
}

void ControllerDialog::on_mouseResizeLineXViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getMouseResizeLineX(), this);
    dialog.exec();
}

void ControllerDialog::on_mouseResizeLineYViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getMouseResizeLineY(), this);
    dialog.exec();
}

void ControllerDialog::on_mouseResizeCellViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getMouseResizeCell(), this);
    dialog.exec();
}

void ControllerDialog::on_mousePressedViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getMousePressed(), this);
    dialog.exec();
}

void ControllerDialog::on_ctrlPressedViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getCtrlPressed(), this);
    dialog.exec();
}

void ControllerDialog::on_shiftPressedViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getShiftPressed(), this);
    dialog.exec();
}

void ControllerDialog::on_mouseLocationViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getMouseLocation(), this);
    dialog.exec();
}

void ControllerDialog::on_mouseLocationForShiftViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getMouseLocationForShift(), this);
    dialog.exec();
}

void ControllerDialog::on_mouseSelectedCellsViewButton_clicked()
{
    ViewDialog dialog(((PublicCustomFastTable*)mFastTableWidget)->getMouseSelectedCells(), this);
    dialog.exec();
}

void ControllerDialog::on_mergeParentViewButton_clicked()
{
    QList<QStringList> aList;

    for (int i=0; i<mFastTableWidget->rowCount(); i++)
    {
        QStringList aRow;

        for (int j=0; j<mFastTableWidget->columnCount(); j++)
        {
            QPoint aPoint=((FastTableWidget*)mFastTableWidget)->spanParent(i, j);

            aRow.append(QString::number(aPoint.y())+" "+QString::number(aPoint.x()));
        }

        aList.append(aRow);
    }

    ViewDialog dialog(&aList, this);
    dialog.exec();
}

void ControllerDialog::on_mergeXYViewButton_clicked()
{
    QList<QStringList> aList;

    for (int i=0; i<mFastTableWidget->rowCount(); i++)
    {
        QStringList aRow;

        for (int j=0; j<mFastTableWidget->columnCount(); j++)
        {
            aRow.append(QString::number(((FastTableWidget*)mFastTableWidget)->columnSpan(i, j))+" "+QString::number(((FastTableWidget*)mFastTableWidget)->rowSpan(i, j)));
        }

        aList.append(aRow);
    }

    ViewDialog dialog(&aList, this);
    dialog.exec();
}

void ControllerDialog::on_mergesViewButton_clicked()
{
    ViewDialog dialog(((PublicFastTable*)mFastTableWidget)->getMerges(), this);
    dialog.exec();
}

void ControllerDialog::on_horizontalMergeParentViewButton_clicked()
{
    QList<QStringList> aList;

    for (int i=0; i<mFastTableWidget->horizontalHeader_RowCount(); i++)
    {
        QStringList aRow;

        for (int j=0; j<mFastTableWidget->columnCount(); j++)
        {
            QPoint aPoint=((FastTableWidget*)mFastTableWidget)->horizontalHeader_SpanParent(i, j);

            aRow.append(QString::number(aPoint.y())+" "+QString::number(aPoint.x()));
        }

        aList.append(aRow);
    }

    ViewDialog dialog(&aList, this);
    dialog.exec();
}

void ControllerDialog::on_horizontalMergeXYViewButton_clicked()
{
    QList<QStringList> aList;

    for (int i=0; i<mFastTableWidget->horizontalHeader_RowCount(); i++)
    {
        QStringList aRow;

        for (int j=0; j<mFastTableWidget->columnCount(); j++)
        {
            aRow.append(QString::number(((FastTableWidget*)mFastTableWidget)->horizontalHeader_ColumnSpan(i, j))+" "+QString::number(((FastTableWidget*)mFastTableWidget)->horizontalHeader_RowSpan(i, j)));
        }

        aList.append(aRow);
    }

    ViewDialog dialog(&aList, this);
    dialog.exec();
}

void ControllerDialog::on_horizontalMergesViewButton_clicked()
{
    ViewDialog dialog(((PublicFastTable*)mFastTableWidget)->horizontalHeader_GetMerges(), this);
    dialog.exec();
}

void ControllerDialog::on_verticalMergeParentViewButton_clicked()
{
    QList<QStringList> aList;

    for (int i=0; i<mFastTableWidget->rowCount(); i++)
    {
        QStringList aRow;

        for (int j=0; j<mFastTableWidget->verticalHeader_ColumnCount(); j++)
        {
            QPoint aPoint=((FastTableWidget*)mFastTableWidget)->verticalHeader_SpanParent(i, j);

            aRow.append(QString::number(aPoint.y())+" "+QString::number(aPoint.x()));
        }

        aList.append(aRow);
    }

    ViewDialog dialog(&aList, this);
    dialog.exec();
}

void ControllerDialog::on_verticalMergeXYViewButton_clicked()
{
    QList<QStringList> aList;

    for (int i=0; i<mFastTableWidget->rowCount(); i++)
    {
        QStringList aRow;

        for (int j=0; j<mFastTableWidget->verticalHeader_ColumnCount(); j++)
        {
            aRow.append(QString::number(((FastTableWidget*)mFastTableWidget)->verticalHeader_ColumnSpan(i, j))+" "+QString::number(((FastTableWidget*)mFastTableWidget)->verticalHeader_RowSpan(i, j)));
        }

        aList.append(aRow);
    }

    ViewDialog dialog(&aList, this);
    dialog.exec();
}

void ControllerDialog::on_verticalMergesViewButton_clicked()
{
    ViewDialog dialog(((PublicFastTable*)mFastTableWidget)->verticalHeader_GetMerges(), this);
    dialog.exec();
}

void ControllerDialog::tableInsertRow()
{
    if (mFastTableWidget->currentRow()>=0)
    {
        mFastTableWidget->insertRow(mFastTableWidget->currentRow());

        ui->rowCountSpinBox->blockSignals(true);
        ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
        ui->rowCountSpinBox->blockSignals(false);
    }
}

void ControllerDialog::tableDeleteRow()
{
    QList<int> rows;

    for (int i=mFastTableWidget->rowCount()-1; i>=0; i--)
    {
        if (mFastTableWidget->rowHasSelection(i))
        {
            rows.append(i);
        }
    }

    for (int i=0; i<rows.length(); i++)
    {
        mFastTableWidget->removeRow(rows.at(i));
    }

    ui->rowCountSpinBox->blockSignals(true);
    ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
    ui->rowCountSpinBox->blockSignals(false);
}

void ControllerDialog::tableInsertColumn()
{
    if (mFastTableWidget->currentColumn()>=0)
    {
        mFastTableWidget->insertColumn(mFastTableWidget->currentColumn());

        ui->columnCountSpinBox->blockSignals(true);
        ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
        ui->columnCountSpinBox->blockSignals(false);
    }
}

void ControllerDialog::tableDeleteColumn()
{
    QList<int> columns;

    for (int i=mFastTableWidget->columnCount()-1; i>=0; i--)
    {
        if (mFastTableWidget->columnHasSelection(i))
        {
            columns.append(i);
        }
    }

    for (int i=0; i<columns.length(); i++)
    {
        mFastTableWidget->removeColumn(columns.at(i));
    }

    ui->columnCountSpinBox->blockSignals(true);
    ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
    ui->columnCountSpinBox->blockSignals(false);
}

void ControllerDialog::tableMergeCells()
{
     QList<QRect> aRanges=mFastTableWidget->selectedRanges();

     if (aRanges.length()>0)
     {
         ((FastTableWidget*)mFastTableWidget)->setSpan(aRanges.at(0));
     }
}

void ControllerDialog::tableContextMenuRequested(QPoint /*pos*/)
{
    QMenu *contextMenu=new QMenu;

    contextMenu->addAction("Insert row",this,SLOT(tableInsertRow()));
    contextMenu->addAction("Delete row(s)",this,SLOT(tableDeleteRow()));
    contextMenu->addAction("Insert column",this,SLOT(tableInsertColumn()));
    contextMenu->addAction("Delete column(s)",this,SLOT(tableDeleteColumn()));

    if (ui->fastTableControlWidget->isVisible())
    {
        contextMenu->addSeparator();
        contextMenu->addAction("Merge cells",this,SLOT(tableMergeCells()));
    }

    contextMenu->setGeometry(cursor().pos().x(),cursor().pos().y(),contextMenu->sizeHint().width(),contextMenu->sizeHint().height());
    contextMenu->show();
}

void ControllerDialog::on_createCustomTableButton_clicked()
{
    mFastTableWidget=new CustomFastTableWidget(this);
    ui->fastTableLayout->addWidget(mFastTableWidget);

    ui->defaultWidthSpinBox->setValue(100);
    ui->defaultHeightSpinBox->setValue(30);

    ui->rowCountSpinBox->setValue(0);
    ui->columnCountSpinBox->setValue(0);
    ui->horizontalHeaderRowCountSpinBox->setValue(0);
    ui->verticalHeaderColumnCountSpinBox->setValue(0);

    ui->rowCountSpinBox->setValue(100);
    ui->columnCountSpinBox->setValue(10);
    ui->horizontalHeaderRowCountSpinBox->setValue(1);
    ui->verticalHeaderColumnCountSpinBox->setValue(1);

    for (int i=0; i<mFastTableWidget->rowCount(); ++i)
    {
        for (int j=0; j<mFastTableWidget->columnCount(); ++j)
        {
            mFastTableWidget->setText(i, j, "C_"+QString::number(i)+"_"+QString::number(j));
        }
    }

    for (int i=0; i<mFastTableWidget->columnCount(); ++i)
    {
        mFastTableWidget->horizontalHeader_SetText(i, "Header_"+QString::number(i));
    }

    mFastTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mFastTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tableContextMenuRequested(QPoint)));

    ui->fastTableControlWidget->setVisible(false);

    setStyleButtonsFlat();

    ui->mainStackedWidget->setCurrentIndex(0);
}

void ControllerDialog::on_createFastTableButton_clicked()
{
    mFastTableWidget=new FastTableWidget(this);
    ui->fastTableLayout->addWidget(mFastTableWidget);

    ui->defaultWidthSpinBox->setValue(100);
    ui->defaultHeightSpinBox->setValue(30);

    ui->rowCountSpinBox->setValue(0);
    ui->columnCountSpinBox->setValue(0);
    ui->horizontalHeaderRowCountSpinBox->setValue(0);
    ui->verticalHeaderColumnCountSpinBox->setValue(0);

    ui->rowCountSpinBox->setValue(100);
    ui->columnCountSpinBox->setValue(10);
    ui->horizontalHeaderRowCountSpinBox->setValue(1);
    ui->verticalHeaderColumnCountSpinBox->setValue(1);

    for (int i=0; i<mFastTableWidget->rowCount(); ++i)
    {
        for (int j=0; j<mFastTableWidget->columnCount(); ++j)
        {
            mFastTableWidget->setText(i, j, "C_"+QString::number(i)+"_"+QString::number(j));
        }
    }

    for (int i=0; i<mFastTableWidget->columnCount(); ++i)
    {
        mFastTableWidget->horizontalHeader_SetText(i, "Header_"+QString::number(i));
    }

    mFastTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mFastTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tableContextMenuRequested(QPoint)));

    ui->fastTableControlWidget->setVisible(true);

    setStyleButtonsFlat();

    ui->mainStackedWidget->setCurrentIndex(0);
}
