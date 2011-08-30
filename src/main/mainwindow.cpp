#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/main/testdialog.h"

#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    FastTableWidget* aFastTableWidget=new FastTableWidget(this);
    ui->fastTableLayout->addWidget(aFastTableWidget);

    clock_t aStart=clock();

    aFastTableWidget->setRowCount(50);
    aFastTableWidget->setColumnCount(20);
    //aFastTableWidget->setRowCount(30000);
    //aFastTableWidget->setColumnCount(500);

    for (int i=0; i<aFastTableWidget->rowCount(); i++)
    {
        aFastTableWidget->setText(i, 0, QString::number(i+1));
    }

    for (int i=0; i<aFastTableWidget->rowCount(); i++)
    {
        for (int j=1; j<aFastTableWidget->columnCount(); j++)
        {
            aFastTableWidget->setText(i, j, "A");
        }
    }

    qDebug()<<"Time to fill with data:"<<(int)(((double)(clock()-aStart))/CLOCKS_PER_SEC*1000)<<"ms";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testButton_clicked()
{
    TestDialog dialog(this);
    dialog.exec();
}
