#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    CustomFastTableWidget* aFastTableWidget=new CustomFastTableWidget(this);
    ui->fastTableLayout->addWidget(aFastTableWidget);

    qint64 aStart=QDateTime::currentMSecsSinceEpoch();

    aFastTableWidget->setRowCount(50);
    aFastTableWidget->setColumnCount(20);
    aFastTableWidget->horizontalHeader_SetRowCount(3);
    aFastTableWidget->verticalHeader_SetColumnCount(1);
    //aFastTableWidget->setRowCount(30000);
    //aFastTableWidget->setColumnCount(250);

    for (int i=0; i<aFastTableWidget->rowCount(); i++)
    {
        aFastTableWidget->setText(i, 0, QString::number(i+1));
    }

    for (int i=0; i<aFastTableWidget->rowCount(); i++)
    {
        for (int j=1; j<aFastTableWidget->columnCount(); j++)
        {
            aFastTableWidget->setText(i, j, "Hello, Wolrd");
        }
    }

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
