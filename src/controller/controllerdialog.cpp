#include "controllerdialog.h"

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mFastTableWidget=new FastTableWidget(this);
    ui->fastTableLayout->insertWidget(0, mFastTableWidget);

    ui->defaultWidthSpinBox->setValue(100);
    ui->defaultHeightSpinBox->setValue(30);

    ui->rowCountSpinBox->setValue(50);
    ui->columnCountSpinBox->setValue(20);
    ui->horizontalHeaderRowCountSpinBox->setValue(1);
    ui->verticalHeaderColumnCountSpinBox->setValue(1);

    for (int i=0; i<mFastTableWidget->rowCount(); ++i)
    {
        for (int j=0; j<mFastTableWidget->columnCount(); ++j)
        {
            mFastTableWidget->setText(i, j, "Hello, World");
        }
    }

    for (int i=0; i<mFastTableWidget->columnCount(); ++i)
    {
        mFastTableWidget->horizontalHeader_SetText(i, "Header");
    }
}

ControllerDialog::~ControllerDialog()
{
    delete ui;
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

    disconnect(ui->rowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_rowCountSpinBox_valueChanged(int)));
    ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
    connect(ui->rowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_rowCountSpinBox_valueChanged(int)));
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

        disconnect(ui->rowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_rowCountSpinBox_valueChanged(int)));
        ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
        connect(ui->rowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_rowCountSpinBox_valueChanged(int)));
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
            mFastTableWidget->deleteRow(dialog.intValue());

            disconnect(ui->rowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_rowCountSpinBox_valueChanged(int)));
            ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
            connect(ui->rowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_rowCountSpinBox_valueChanged(int)));
        }
    }
}

void ControllerDialog::on_addColumnButton_clicked()
{
    mFastTableWidget->addColumn();

    disconnect(ui->columnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_columnCountSpinBox_valueChanged(int)));
    ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
    connect(ui->columnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_columnCountSpinBox_valueChanged(int)));
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

        disconnect(ui->columnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_columnCountSpinBox_valueChanged(int)));
        ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
        connect(ui->columnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_columnCountSpinBox_valueChanged(int)));
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
            mFastTableWidget->deleteColumn(dialog.intValue());

            disconnect(ui->columnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_columnCountSpinBox_valueChanged(int)));
            ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
            connect(ui->columnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_columnCountSpinBox_valueChanged(int)));
        }
    }
}

void ControllerDialog::on_addHeaderRowButton_clicked()
{
    mFastTableWidget->horizontalHeader_AddRow();

    disconnect(ui->horizontalHeaderRowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalHeaderRowCountSpinBox_valueChanged(int)));
    ui->horizontalHeaderRowCountSpinBox->setValue(mFastTableWidget->horizontalHeader_RowCount());
    connect(ui->horizontalHeaderRowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalHeaderRowCountSpinBox_valueChanged(int)));
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

        disconnect(ui->horizontalHeaderRowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalHeaderRowCountSpinBox_valueChanged(int)));
        ui->horizontalHeaderRowCountSpinBox->setValue(mFastTableWidget->horizontalHeader_RowCount());
        connect(ui->horizontalHeaderRowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalHeaderRowCountSpinBox_valueChanged(int)));
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
            mFastTableWidget->horizontalHeader_DeleteRow(dialog.intValue());

            disconnect(ui->horizontalHeaderRowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalHeaderRowCountSpinBox_valueChanged(int)));
            ui->horizontalHeaderRowCountSpinBox->setValue(mFastTableWidget->horizontalHeader_RowCount());
            connect(ui->horizontalHeaderRowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalHeaderRowCountSpinBox_valueChanged(int)));
        }
    }
}

void ControllerDialog::on_addHeaderColumnButton_clicked()
{
    mFastTableWidget->verticalHeader_AddColumn();

    disconnect(ui->verticalHeaderColumnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_verticalHeaderColumnCountSpinBox_valueChanged(int)));
    ui->verticalHeaderColumnCountSpinBox->setValue(mFastTableWidget->verticalHeader_ColumnCount());
    connect(ui->verticalHeaderColumnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_verticalHeaderColumnCountSpinBox_valueChanged(int)));
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

        disconnect(ui->verticalHeaderColumnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_verticalHeaderColumnCountSpinBox_valueChanged(int)));
        ui->verticalHeaderColumnCountSpinBox->setValue(mFastTableWidget->verticalHeader_ColumnCount());
        connect(ui->verticalHeaderColumnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_verticalHeaderColumnCountSpinBox_valueChanged(int)));
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
            mFastTableWidget->verticalHeader_DeleteColumn(dialog.intValue());

            disconnect(ui->verticalHeaderColumnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_verticalHeaderColumnCountSpinBox_valueChanged(int)));
            ui->verticalHeaderColumnCountSpinBox->setValue(mFastTableWidget->verticalHeader_ColumnCount());
            connect(ui->verticalHeaderColumnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_verticalHeaderColumnCountSpinBox_valueChanged(int)));
        }
    }
}

void ControllerDialog::on_clearButton_clicked()
{
    mFastTableWidget->clear();

    disconnect(ui->rowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_rowCountSpinBox_valueChanged(int)));
    disconnect(ui->columnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_columnCountSpinBox_valueChanged(int)));
    disconnect(ui->horizontalHeaderRowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalHeaderRowCountSpinBox_valueChanged(int)));
    disconnect(ui->verticalHeaderColumnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_verticalHeaderColumnCountSpinBox_valueChanged(int)));
    ui->rowCountSpinBox->setValue(mFastTableWidget->rowCount());
    ui->columnCountSpinBox->setValue(mFastTableWidget->columnCount());
    ui->horizontalHeaderRowCountSpinBox->setValue(mFastTableWidget->horizontalHeader_RowCount());
    ui->verticalHeaderColumnCountSpinBox->setValue(mFastTableWidget->verticalHeader_ColumnCount());
    connect(ui->rowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_rowCountSpinBox_valueChanged(int)));
    connect(ui->columnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_columnCountSpinBox_valueChanged(int)));
    connect(ui->horizontalHeaderRowCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalHeaderRowCountSpinBox_valueChanged(int)));
    connect(ui->verticalHeaderColumnCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_verticalHeaderColumnCountSpinBox_valueChanged(int)));
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
    QColorDialog dialog(this);

    dialog.setWindowTitle("Default background color");
    dialog.setCurrentColor(mFastTableWidget->defaultBackgroundBrush().color());

    if (dialog.exec())
    {
        mFastTableWidget->setDefaultBackgroundBrush(QBrush(dialog.selectedColor()));
    }
}

void ControllerDialog::on_defaultForegroundButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Default foreground color");
    dialog.setCurrentColor(mFastTableWidget->defaultForegroundColor());

    if (dialog.exec())
    {
        mFastTableWidget->setDefaultForegroundColor(dialog.selectedColor());
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

void ControllerDialog::on_selectionColorButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Selection color");
    dialog.setCurrentColor(mFastTableWidget->selectionBrush().color());

    if (dialog.exec())
    {
        mFastTableWidget->setSelectionBrush(QBrush(dialog.selectedColor()));
    }
}

void ControllerDialog::on_selectionTextColorButton_clicked()
{
    QColorDialog dialog(this);

    dialog.setWindowTitle("Selection text color");
    dialog.setCurrentColor(mFastTableWidget->selectionTextColor());

    if (dialog.exec())
    {
        mFastTableWidget->setSelectionTextColor(dialog.selectedColor());
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

            if (dialog.exec())
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

            if (dialog.exec())
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

            if (dialog.exec())
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

}

void ControllerDialog::on_rowHeightViewButton_clicked()
{

}

void ControllerDialog::on_headerColumnWidthViewButton_clicked()
{

}

void ControllerDialog::on_headerRowHeightViewButton_clicked()
{

}

void ControllerDialog::on_totalWidthViewButton_clicked()
{

}

void ControllerDialog::on_totalHeightViewButton_clicked()
{

}

void ControllerDialog::on_headerTotalWidthViewButton_clicked()
{

}

void ControllerDialog::on_headerTotalHeightViewButton_clicked()
{

}

void ControllerDialog::on_visibleRangesViewButton_clicked()
{

}

void ControllerDialog::on_horizontalVisibleRangesViewButton_clicked()
{

}

void ControllerDialog::on_verticalVisibleRangesViewButton_clicked()
{

}

void ControllerDialog::on_textViewButton_clicked()
{

}

void ControllerDialog::on_horizontalTextViewButton_clicked()
{

}

void ControllerDialog::on_verticalTextViewButton_clicked()
{

}

void ControllerDialog::on_cellSelectedButton_clicked()
{

}

void ControllerDialog::on_cellSelectedViewButton_clicked()
{

}

void ControllerDialog::on_currentSelectionViewButton_clicked()
{

}

void ControllerDialog::on_rowsSelectedViewButton_clicked()
{

}

void ControllerDialog::on_columnsSelectedViewButton_clicked()
{

}
