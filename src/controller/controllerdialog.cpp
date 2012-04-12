#include "controllerdialog.h"

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog)
{
    ui->setupUi(this);

    mFastTableWidget=new FastTableWidget(this);
    ui->fastTableLayout->insertWidget(0, mFastTableWidget);

    mFastTableWidget->setRowCount(50);
    mFastTableWidget->setColumnCount(20);
    mFastTableWidget->horizontalHeader_SetRowCount(1);
    mFastTableWidget->verticalHeader_SetColumnCount(1);

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
