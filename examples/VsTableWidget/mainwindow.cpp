#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    StatisticsFrame* aFrame;

    aFrame=new StatisticsFrame(new QTableWidget(this), this);
    mFrames.append(aFrame);
    ui->mainHorizontalLayout->addWidget(aFrame);

    aFrame=new StatisticsFrame(new CustomFastTableWidget(this), this);
    mFrames.append(aFrame);
    ui->mainTabWidget->addTab(aFrame, "CustomFastTableWidget");

    aFrame=new StatisticsFrame(new FastTableWidget(this), this);
    mFrames.append(aFrame);
    ui->mainTabWidget->addTab(aFrame, "FastTableWidget");

    QTimer::singleShot(0, this, SLOT(startComparing()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startComparing()
{
    for (int i=0; i<mFrames.length(); i++)
    {
        if (i==0)
        {
            ui->mainTabWidget->setCurrentIndex(0);
        }
        else
        {
            ui->mainTabWidget->setCurrentIndex(i-1);
        }

        mFrames.at(i)->startGetData();
    }
}
