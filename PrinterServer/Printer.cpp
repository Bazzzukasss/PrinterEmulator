#include "Printer.h"
#include "Protocol.h"
#include <QTimer>

Printer::Printer(QObject *parent)
    : QObject(parent)
{
    int i(0);
    QString names[AXIS_COUNT]={"X","Y","Size"};
    while( ++i <= AXIS_COUNT )
        mHead.mAxises.push_back(PrinterHeadAxis( i-1 , names[i-1]));

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, [&](){ moving(); });
    mTimer->start(100);
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

void Printer::moving()
{
    if(!mHead.makeStep())
        mIsBusy = false;
    else
        emit signalStateChanged(mHead);
}


