#include <QtGui/QApplication>
#include "src/main/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug()<<"Application started";

    MainWindow w;
    w.show();

    return a.exec();
}
