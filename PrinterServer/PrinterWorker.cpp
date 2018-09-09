#include "PrinterWorker.h"
#include <QDebug>
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

PrinterWorker::PrinterWorker(QObject *parent)
    : QObject(parent)
{

}

void PrinterWorker::stop()
{
    isStoped = true;
}

void PrinterWorker::slotStart()
{
    while(!isStoped)
    {
        pPRINTER->makeStep();
        std::this_thread::sleep_for(100ms);
    }
}

