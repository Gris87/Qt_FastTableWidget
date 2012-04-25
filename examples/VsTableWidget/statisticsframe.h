#ifndef STATISTICSFRAME_H
#define STATISTICSFRAME_H

#include <QWidget>
#include "ui_statisticsframe.h"

#include <QTableWidget>

#include "../../src/fasttable/fasttablewidget.h"

namespace Ui {
    class StatisticsFrame;
}

class StatisticsFrame : public QWidget
{
    Q_OBJECT

public:
    Ui::StatisticsFrame *ui;
    QWidget *mTableWidget;

    explicit StatisticsFrame(QWidget *tableWidget, QWidget *parent = 0);
    ~StatisticsFrame();

    void startGetData();
};

#endif // STATISTICSFRAME_H
