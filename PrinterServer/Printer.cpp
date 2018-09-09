#include "Printer.h"
#include "Protocol.h"
#include "PrinterWorker.h"

Printer::Printer(QObject *parent)
    : QObject(parent)
{
    int i(0);
    QString names[AXIS_COUNT]={"X","Y","Size"};
    while( ++i <= AXIS_COUNT )
        mHead.mAxises.push_back(PrinterHeadAxis( i-1 , names[i-1]));

    mpWorker = new PrinterWorker();
    mpWorker->moveToThread(&mWorkerThread);
    connect(&mWorkerThread, &QThread::finished,             mpWorker,    &QObject::deleteLater);
    connect(this, &Printer::signalStartWorker,              mpWorker,    &PrinterWorker::slotStart);

    mWorkerThread.start();
    emit signalStartWorker();
}

Printer::~Printer()
{
    mpWorker->stop();
    mWorkerThread.quit();
    mWorkerThread.wait();
}

bool Printer::moveHead(int aAxisId, int aStepsCount, int aDirection, QColor aColor)
{
    if(mIsBusy)
        return false;

    mIsBusy = true;

    PrinterHeadAxis* pAxis = &mHead.mAxises[aAxisId];

    pAxis->mStepsCount = aStepsCount;
    pAxis->mDirection = aDirection;
    mHead.mColor = aColor;
    return true;
}

int Printer::getSensorValue(int aAxisId)
{
    return mHead.mAxises[aAxisId].mValue;
}

bool Printer::makeStep()
{
    bool res = mHead.makeStep();
    if(res)
        emit signalStateChanged(mHead);
    else
        mIsBusy = false;

    return res;
}

void Printer::moving()
{
    if(!mHead.makeStep())
        mIsBusy = false;
    else
        emit signalStateChanged(mHead);
}


