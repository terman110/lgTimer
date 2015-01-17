#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName( "lgTimer");
    a.setApplicationVersion("1.0.0");
    a.setApplicationDisplayName("lgTimer");

    MainWindow w;
    w.show();

    return a.exec();
}
