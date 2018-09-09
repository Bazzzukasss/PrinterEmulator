#include "PrinterWorker.h"
#include <QDebug>
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

PrinterWorker::PrinterWorker(QObject *parent)
    : QObject(parent)
{

}

void PrinterWorker::slotStart()
{
    while(true)
    {
        if(pPRINTER->makeStep())
            qDebug()<<"Steps left";
        std::this_thread::sleep_for(100ms);
    }
}
