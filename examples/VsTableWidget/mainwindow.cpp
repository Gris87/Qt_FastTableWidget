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

    aFrame=new StatisticsFrame(new CustomFastTableWidget(this), this);
    mFrames.append(aFrame);
    ui->mainTabWidget->addTab(aFrame, "CustomFastTableWidget");

    aFrame=new StatisticsFrame(new FastTableWidget(this), this);
    mFrames.append(aFrame);
    ui->mainTabWidget->addTab(aFrame, "FastTableWidget");

    aFrame=new StatisticsFrame(new QTableWidget(this), this);
    mFrames.append(aFrame);
    ui->mainHorizontalLayout->addWidget(aFrame);

    ui->cloneTabWidget->setVisible(false);

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
        if (i<mFrames.length()-1)
        {
            ui->mainTabWidget->setCurrentIndex(i);
        }

        mFrames.at(i)->startGetData();
    }

    for (int i=0; i<mFrames.length(); i++)
    {
        delete mFrames.at(i)->mTableWidget;
    }

    ui->mainHorizontalLayout->removeWidget(mFrames.last());
    ui->mainTabWidget->addTab(mFrames.last(), "QTableWidget");

    for (int i=0; i<ui->mainTabWidget->count(); i++)
    {
        ui->cloneTabWidget->addTab(new StatisticsFrame((StatisticsFrame*)ui->mainTabWidget->widget(i), this), ui->mainTabWidget->tabText(i));
    }

    ui->cloneTabWidget->setVisible(true);

    resize(width(), 0);

    ui->mainTabWidget->setCurrentIndex(0);
    ui->cloneTabWidget->setCurrentIndex(ui->cloneTabWidget->count()-1);

    connect(ui->mainTabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    connect(ui->cloneTabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    tabChanged(-1);
}

void MainWindow::tabChanged(int index)
{
    StatisticsFrame *aLeftFrame=(StatisticsFrame *)ui->mainTabWidget->currentWidget();
    StatisticsFrame *aRightFrame=(StatisticsFrame *)ui->cloneTabWidget->currentWidget();

    compareLabels(aLeftFrame->ui->maximumCountResLabel,      aRightFrame->ui->maximumCountResLabel,      false);
    compareLabels(aLeftFrame->ui->timeToAppendResLabel,      aRightFrame->ui->timeToAppendResLabel,      true);
    compareLabels(aLeftFrame->ui->timeToDeleteEndResLabel,   aRightFrame->ui->timeToDeleteEndResLabel,   true);
    compareLabels(aLeftFrame->ui->timeToInsertResLabel,      aRightFrame->ui->timeToInsertResLabel,      true);
    compareLabels(aLeftFrame->ui->timeToDeleteBeginResLabel, aRightFrame->ui->timeToDeleteBeginResLabel, true);
}

void MainWindow::compareLabels(QLabel *label1, QLabel *label2, bool lessBetter)
{
    QString text1=label1->text();
    QString text2=label2->text();

    text1=text1.remove(" ").remove("ms");
    text2=text2.remove(" ").remove("ms");

    if (text1==text2)
    {
        QPalette aPalette;

        aPalette.setColor(QPalette::WindowText, QColor(0, 0, 0));

        label1->setPalette(aPalette);
        label2->setPalette(aPalette);
    }
    else
    {
        QPalette redPalette;
        QPalette greenPalette;

        redPalette.setColor(QPalette::WindowText, QColor(128, 0, 0));
        greenPalette.setColor(QPalette::WindowText, QColor(0, 128, 0));

        if ((text1.toLongLong()<text2.toLongLong())==lessBetter)
        {
            label1->setPalette(greenPalette);
            label2->setPalette(redPalette);
        }
        else
        {
            label1->setPalette(redPalette);
            label2->setPalette(greenPalette);
        }
    }
}
