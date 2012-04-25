#include "statisticsframe.h"

StatisticsFrame::StatisticsFrame(QWidget *tableWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsFrame)
{
    ui->setupUi(this);

    mTableWidget=tableWidget;
    ui->frameVerticalLayout->insertWidget(0, mTableWidget);
}

StatisticsFrame::StatisticsFrame(StatisticsFrame *frame, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsFrame)
{
    ui->setupUi(this);

    ui->maximumCountResLabel->setText     (frame->ui->maximumCountResLabel->text());
    ui->timeToAppendResLabel->setText     (frame->ui->timeToAppendResLabel->text());
    ui->timeToDeleteEndResLabel->setText  (frame->ui->timeToDeleteEndResLabel->text());
    ui->timeToInsertResLabel->setText     (frame->ui->timeToInsertResLabel->text());
    ui->timeToDeleteBeginResLabel->setText(frame->ui->timeToDeleteBeginResLabel->text());
}


StatisticsFrame::~StatisticsFrame()
{
    delete ui;
}

void StatisticsFrame::startGetData()
{
    if (mTableWidget->inherits("QTableWidget"))
    {
        qint64 aStartTime;
        QTableWidget *aTableWidget=(QTableWidget *)mTableWidget;

#ifdef MAXCOUNT_TABLEWIDGET
        ui->maximumCountResLabel->setText(numberWithSpaces(MAXCOUNT_TABLEWIDGET));
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
#else
        aTableWidget->setColumnCount(1000);

        for (int i=0; ; i++)
        {
            ui->maximumCountResLabel->setText(numberWithSpaces(i*aTableWidget->columnCount()));

            try
            {
                void *buffer=malloc(65535);

                if (buffer)
                {
                    free(buffer);
                }
                else
                {
                    throw "Finished";
                }

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
#endif

//--------------------------------------------------------------------------------------------------

        aStartTime=QDateTime::currentMSecsSinceEpoch();

        aTableWidget->setColumnCount(1000);

        for (int i=0; i<1000; i++)
        {
            aTableWidget->insertRow(i);

            for (int j=0; j<aTableWidget->columnCount(); j++)
            {
                aTableWidget->setItem(i, j, new QTableWidgetItem("Hello"));
            }

            if ((i+1) % 100==0)
            {
                ui->timeToAppendResLabel->setText(numberWithSpaces(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }

//--------------------------------------------------------------------------------------------------

        aStartTime=QDateTime::currentMSecsSinceEpoch();

        for (int i=999; i>=0; i--)
        {
            aTableWidget->removeRow(i);

            if (i % 100==0)
            {
                ui->timeToDeleteEndResLabel->setText(numberWithSpaces(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }

//--------------------------------------------------------------------------------------------------

        aStartTime=QDateTime::currentMSecsSinceEpoch();

        aTableWidget->setColumnCount(1000);

        for (int i=0; i<1000; i++)
        {
            aTableWidget->insertRow(0);

            for (int j=0; j<aTableWidget->columnCount(); j++)
            {
                aTableWidget->setItem(0, j, new QTableWidgetItem("Hello"));
            }

            if ((i+1) % 100==0)
            {
                ui->timeToInsertResLabel->setText(numberWithSpaces(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }

//--------------------------------------------------------------------------------------------------

        aStartTime=QDateTime::currentMSecsSinceEpoch();

        for (int i=999; i>=0; i--)
        {
            aTableWidget->removeRow(0);

            if (i % 100==0)
            {
                ui->timeToDeleteBeginResLabel->setText(numberWithSpaces(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }
    }

    else
    {
        qint64 aStartTime;
        CustomFastTableWidget *aTableWidget=(CustomFastTableWidget *)mTableWidget;

        if (aTableWidget->inherits("FastTableWidget"))
        {
#ifdef MAXCOUNT_FASTTABLEWIDGET
            ui->maximumCountResLabel->setText(numberWithSpaces(MAXCOUNT_FASTTABLEWIDGET));
            QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
#endif
        }
        else
        {
#ifdef MAXCOUNT_CUSTOMFASTTABLEWIDGET
            ui->maximumCountResLabel->setText(numberWithSpaces(MAXCOUNT_CUSTOMFASTTABLEWIDGET));
            QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
#endif
        }

        if (ui->maximumCountResLabel->text()=="0")
        {
            aTableWidget->setSizes(0, 1000);

            for (int i=0; ; i++)
            {
                ui->maximumCountResLabel->setText(numberWithSpaces(i*aTableWidget->columnCount()));

                try
                {
                    void *buffer=malloc(65535);

                    if (buffer)
                    {
                        free(buffer);
                    }
                    else
                    {
                        throw "Finished";
                    }

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

//--------------------------------------------------------------------------------------------------

        aStartTime=QDateTime::currentMSecsSinceEpoch();

        aTableWidget->setSizes(0, 1000);

        for (int i=0; i<1000; i++)
        {
            aTableWidget->insertRow(i);

            for (int j=0; j<aTableWidget->columnCount(); j++)
            {
                aTableWidget->setText(i, j, "Hello");
            }

            if ((i+1) % 100==0)
            {
                ui->timeToAppendResLabel->setText(numberWithSpaces(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }

//--------------------------------------------------------------------------------------------------

        aStartTime=QDateTime::currentMSecsSinceEpoch();

        for (int i=999; i>=0; i--)
        {
            aTableWidget->deleteRow(i);

            if (i % 100==0)
            {
                ui->timeToDeleteEndResLabel->setText(numberWithSpaces(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }

//--------------------------------------------------------------------------------------------------

        aStartTime=QDateTime::currentMSecsSinceEpoch();

        aTableWidget->setSizes(0, 1000);

        for (int i=0; i<1000; i++)
        {
            aTableWidget->insertRow(0);

            for (int j=0; j<aTableWidget->columnCount(); j++)
            {
                aTableWidget->setText(0, j, "Hello");
            }

            if ((i+1) % 100==0)
            {
                ui->timeToInsertResLabel->setText(numberWithSpaces(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }

//--------------------------------------------------------------------------------------------------

        aStartTime=QDateTime::currentMSecsSinceEpoch();

        for (int i=999; i>=0; i--)
        {
            aTableWidget->deleteRow(0);

            if (i % 100==0)
            {
                ui->timeToDeleteBeginResLabel->setText(numberWithSpaces(QDateTime::currentMSecsSinceEpoch()-aStartTime)+" ms");
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }
    }
}

QString StatisticsFrame::numberWithSpaces(qint64 value)
{
    QString res=QString::number(value);

    for (int i=res.length()-3; i>0; i-=3)
    {
        res.insert(i, " ");
    }

    return res;
}
