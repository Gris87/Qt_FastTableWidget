#include <QtGui/QApplication>
#include "src/main/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(Resources);

    MainWindow w;
    w.show();

    return a.exec();
}
