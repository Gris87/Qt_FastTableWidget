#include "statisticsframe.h"

StatisticsFrame::StatisticsFrame(QWidget *tableWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsFrame)
{
    ui->setupUi(this);

    mTableWidget=tableWidget;
    ui->frameVerticalLayout->insertWidget(0, mTableWidget);
}

StatisticsFrame::~StatisticsFrame()
{
    delete ui;
}

void StatisticsFrame::startGetData()
{
    if (mTableWidget->inherits("QTableWidget"))
    {
        qint64 aStartTime=QDateTime::currentMSecsSinceEpoch();

        QTableWidget *aTableWidget=(QTableWidget *)mTableWidget;
        aTableWidget->setColumnCount(1000);

        for (int i=0; i<1; i++)
        {
            ui->maximumCountResLabel->setText(QString::number(i*aTableWidget->columnCount()));
            ui->timeToFillResLabel->setText(QString::number(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");

            try
            {
                aTableWidget->insertRow(i);

                for (int j=0; j<aTableWidget->columnCount(); j++)
                {
                    aTableWidget->setItem(i, j, new QTableWidgetItem("Hello"));
                }
            }
            catch(...)
            {
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
                break;
            }

            if (i % 100 == 0)
            {
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }

        aTableWidget->clearContents();
        aTableWidget->setRowCount(0);
        aTableWidget->setColumnCount(0);
    }
    else
    {
        qint64 aStartTime=QDateTime::currentMSecsSinceEpoch();

        FastTableWidget *aTableWidget=(FastTableWidget *)mTableWidget;
        aTableWidget->setSizes(0, 1000);

        for (int i=0; ; i++)
        {
            ui->maximumCountResLabel->setText(QString::number(i*aTableWidget->columnCount()));
            ui->timeToFillResLabel->setText(QString::number(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");

            try
            {
                aTableWidget->insertRow(i);

                for (int j=0; j<aTableWidget->columnCount(); j++)
                {
                    aTableWidget->setText(i, j, "Hello");
                }
            }
            catch(...)
            {
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
                break;
            }

            if (i % 100 == 0)
            {
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }

        aTableWidget->clear();
    }
}
