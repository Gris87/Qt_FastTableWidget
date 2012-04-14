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

    aFastTableWidget->setSizes(50, 20, 1 ,1);
    //aFastTableWidget->setSizes(30000, 250, 1 ,1);

    for (int i=0; i<aFastTableWidget->rowCount(); ++i)
    {
        for (int j=0; j<aFastTableWidget->columnCount(); ++j)
        {
            aFastTableWidget->setText(i, j, "Hello, World");
        }
    }

    for (int i=0; i<aFastTableWidget->columnCount(); ++i)
    {
        aFastTableWidget->horizontalHeader_SetText(i, "Header");
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

void MainWindow::on_controllerButton_clicked()
{
    ControllerDialog dialog(this);
    dialog.exec();
}
