#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QTableWidget>
#include <QTimer>

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

public slots:
    void startComparing();
};

#endif // MAINWINDOW_H
