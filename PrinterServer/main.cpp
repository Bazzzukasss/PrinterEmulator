#include "mainwindow.h"
#include <QApplication>
#include<QMetaType>
#include "Printer.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<PrinterHead>("PrinterHead");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
