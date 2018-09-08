#include "Printer.h"
#include "Commands.h"

Printer::Printer(QObject *parent)
    : QObject(parent)
{
    initialize();
}

bool Printer::moveHead(int aAxisId, int aStepsCount, int aDirection, int aColor)
{
    if(mIsBusy)
        return false;

    PrinterHeadAxis* pAxis = mHead.mAxises[aAxisId];

    pAxis->mStepsCount = aStepsCount;
    pAxis->mDirection = aDirection;
    mHead.mColor = aColor;

    startMotion();
    return true;
}

int Printer::getCurrentPosition(int aAxisId)
{

}

void Printer::startMotion()
{
    mIsBusy = true;
}

void Printer::stopMotion()
{
    mIsBusy = false;
}

void Printer::moving()
{

}

void Printer::initialize()
{
    int i(0);
    while( ++i <= AXIS_COUNT )
        mHead.mAxises.pushBack(PrinterHeadAxis());
}
