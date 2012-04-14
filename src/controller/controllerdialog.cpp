#include "controllerdialog.h"

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mFastTableWidget=new FastTableWidget(this);
    ui->fastTableLayout->insertWidget(0, mFastTableWidget);

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
}

void ControllerDialog::on_insertRowButton_clicked()
{

}

void ControllerDialog::on_deleteRowButton_clicked()
{

}

void ControllerDialog::on_addColumnButton_clicked()
{

}

void ControllerDialog::on_insertColumnButton_clicked()
{

}

void ControllerDialog::on_deleteColumnButton_clicked()
{

}

void ControllerDialog::on_addHeaderRowButton_clicked()
{

}

void ControllerDialog::on_insertHeaderRowButton_clicked()
{

}

void ControllerDialog::on_deleteHeaderRowButton_clicked()
{

}

void ControllerDialog::on_addHeaderColumnButton_clicked()
{

}

void ControllerDialog::on_insertHeaderColumnButton_clicked()
{

}

void ControllerDialog::on_deleteHeaderColumnButton_clicked()
{

}

void ControllerDialog::on_clearButton_clicked()
{
    mFastTableWidget->clear();

    ui->rowCountSpinBox->setValue(0);
    ui->columnCountSpinBox->setValue(0);
    ui->horizontalHeaderRowCountSpinBox->setValue(0);
    ui->verticalHeaderColumnCountSpinBox->setValue(0);
}

void ControllerDialog::on_selectRowButton_clicked()
{

}

void ControllerDialog::on_unselectRowButton_clicked()
{

}

void ControllerDialog::on_selectColumnButton_clicked()
{

}

void ControllerDialog::on_unselectColumnButton_clicked()
{

}

void ControllerDialog::on_selectAllButton_clicked()
{

}

void ControllerDialog::on_unselectAllButton_clicked()
{

}

void ControllerDialog::on_defaultBackgroundButton_clicked()
{

}

void ControllerDialog::on_defaultForegroundButton_clicked()
{

}

void ControllerDialog::on_gridColorButton_clicked()
{

}

void ControllerDialog::on_horizontalDefaultBackgroundButton_clicked()
{

}

void ControllerDialog::on_horizontalDefaultForegroundButton_clicked()
{

}

void ControllerDialog::on_horizontalGridColorButton_clicked()
{

}

void ControllerDialog::on_verticalDefaultBackgroundButton_clicked()
{

}

void ControllerDialog::on_verticalDefaultForegroundButton_clicked()
{

}

void ControllerDialog::on_verticalGridColorButton_clicked()
{

}

void ControllerDialog::on_selectionColorButton_clicked()
{

}

void ControllerDialog::on_defaultWidthSpinBox_valueChanged(int value)
{

}

void ControllerDialog::on_defaultHeightSpinBox_valueChanged(int value)
{

}

void ControllerDialog::on_columnWidthButton_clicked()
{

}

void ControllerDialog::on_rowHeightButton_clicked()
{

}

void ControllerDialog::on_headerColumnWidthButton_clicked()
{

}

void ControllerDialog::on_headerRowHeightButton_clicked()
{

}

void ControllerDialog::on_textButton_clicked()
{

}

void ControllerDialog::on_horizontalTextButton_clicked()
{

}

void ControllerDialog::on_verticalTextButton_clicked()
{

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

void ControllerDialog::on_defaultBackgroundViewButton_clicked()
{

}

void ControllerDialog::on_defaultForegroundViewButton_clicked()
{

}

void ControllerDialog::on_gridColorViewButton_clicked()
{

}

void ControllerDialog::on_horizontalDefaultBackgroundViewButton_clicked()
{

}

void ControllerDialog::on_horizontalDefaultForegroundViewButton_clicked()
{

}

void ControllerDialog::on_horizontalGridColorViewButton_clicked()
{

}

void ControllerDialog::on_verticalDefaultBackgroundViewButton_clicked()
{

}

void ControllerDialog::on_verticalDefaultForegroundViewButton_clicked()
{

}

void ControllerDialog::on_verticalGridColorViewButton_clicked()
{

}

void ControllerDialog::on_selectionColorViewButton_clicked()
{

}

void ControllerDialog::on_defaultWidthViewButton_clicked()
{

}

void ControllerDialog::on_defaultHeightViewButton_clicked()
{

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
