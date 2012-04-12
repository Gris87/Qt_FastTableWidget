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

void ControllerDialog::on_rowCountButton_clicked()
{

}

void ControllerDialog::on_columnCountButton_clicked()
{

}

void ControllerDialog::on_horizontalHeaderRowCountButton_clicked()
{

}

void ControllerDialog::on_verticalHeaderColumnCountButton_clicked()
{

}
