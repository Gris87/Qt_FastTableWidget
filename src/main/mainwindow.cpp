#include "mainwindow.h"

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

    qint64 aStart=QDateTime::currentMSecsSinceEpoch();

    aFastTableWidget->setRowCount(50);
    aFastTableWidget->setColumnCount(20);
    //aFastTableWidget->setRowCount(30000);
    //aFastTableWidget->setColumnCount(250);
    aFastTableWidget->horizontalHeader_SetRowCount(2);
    aFastTableWidget->verticalHeader_SetColumnCount(1);

    for (int i=0; i<aFastTableWidget->rowCount(); i++)
    {
        for (int j=0; j<aFastTableWidget->columnCount(); j++)
        {
            aFastTableWidget->setText(i, j, "Hello, World");
        }
    }

    for (int i=0; i<aFastTableWidget->columnCount(); i++)
    {
        aFastTableWidget->horizontalHeader_SetText(i, "Header");
    }

    aFastTableWidget->setCellSelected(2, 1, true);

    aFastTableWidget->horizontalHeader_SetBackgroundBrush(0, 2, QBrush(QColor(100, 30, 255)));
    aFastTableWidget->horizontalHeader_SetForegroundColor(1, 1, QColor(100, 30, 255));
    aFastTableWidget->horizontalHeader_SetSpan(0, 0, 1, 2);
    aFastTableWidget->verticalHeader_SetSpan(0, 0, 2, 1);
    /*aFastTableWidget->horizontalHeader_SetBackgroundBrush(0, 2, QBrush(QColor(100, 30, 255)));
    aFastTableWidget->horizontalHeader_SetBackgroundBrush(0, 2, QBrush(QColor(100, 30, 255)));
    aFastTableWidget->horizontalHeader_SetBackgroundBrush(0, 2, QBrush(QColor(100, 30, 255)));
*/
    qDebug()<<"Time to fill with data:"<<QDateTime::currentMSecsSinceEpoch()-aStart<<"ms";
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
