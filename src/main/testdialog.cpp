#include "testdialog.h"

TestDialog::TestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    TestFrame *aFrame;

    aFrame=new TestFrame(new CustomFastTableWidget(this), this);
    ui->testsTabWidget->addTab(aFrame, "CustomFastTableWidget");
    connect(aFrame, SIGNAL(testFinished()), this, SLOT(testCompleted()));
/*
    aFrame=new TestFrame(new FastTableWidget(this), this);
    ui->testsTabWidget->addTab(aFrame, "FastTableWidget");
    connect(aFrame, SIGNAL(testFinished()), this, SLOT(testCompleted()));
*/
    ui->progressBar->setMaximum((((TestFrame*)(ui->testsTabWidget->widget(0)))->ui->testGridLayout->count() >> 1)*ui->testsTabWidget->count());
    ui->progressBar->setValue(0);

    QTimer::singleShot(0, this, SLOT(startTests()));
}

TestDialog::~TestDialog()
{
    delete ui;
}

void TestDialog::startTests()
{
    for (int i=0; i<ui->testsTabWidget->count(); ++i)
    {
        qDebug()<<"========================================================";
        qDebug()<<ui->testsTabWidget->tabText(i);
        qDebug()<<"========================================================";

        ui->testsTabWidget->setCurrentIndex(i);
        ((TestFrame*)(ui->testsTabWidget->widget(i)))->startTest();
    }

    ui->progressBar->setValue(0);
}

void TestDialog::testCompleted()
{
    ui->progressBar->setValue(ui->progressBar->value()+1);
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
}
