#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>

#include "statisticsframe.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    QList<StatisticsFrame *> mFrames;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void compareLabels(QLabel *label1, QLabel *label2, bool lessBetter);

public slots:
    void startComparing();
    void tabChanged(int index);
};

#endif // MAINWINDOW_H
