#include "mainwindow.h"
#include <QApplication>
#include <connection.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.resize(1000, 550);
    //w.showMaximized();
    //w.showFullScreen();

    return a.exec();
}
