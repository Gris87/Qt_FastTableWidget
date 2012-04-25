#ifndef STATISTICSFRAME_H
#define STATISTICSFRAME_H

#include <QWidget>
#include "ui_statisticsframe.h"

#include <QTableWidget>

#include "../../src/fasttable/fasttablewidget.h"

namespace Ui {
    class StatisticsFrame;
}

// Comment this if you want to know your own statistics (It will take 5 minutes)
#define MAXCOUNT_TABLEWIDGET           13500000
#define MAXCOUNT_CUSTOMFASTTABLEWIDGET 39200000
#define MAXCOUNT_FASTTABLEWIDGET       23100000

class StatisticsFrame : public QWidget
{
    Q_OBJECT

public:
    Ui::StatisticsFrame *ui;
    QWidget *mTableWidget;

    explicit StatisticsFrame(QWidget *tableWidget, QWidget *parent = 0);
    explicit StatisticsFrame(StatisticsFrame *frame, QWidget *parent = 0);
    ~StatisticsFrame();

    void startGetData();
    QString numberWithSpaces(qint64 value);
};

#endif // STATISTICSFRAME_H
