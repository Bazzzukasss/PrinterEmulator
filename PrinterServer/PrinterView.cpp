#include "PrinterView.h"
#include "Printer.h"
#include <QDebug>
#include <QGraphicsLineItem>
#include "Protocol.h"

PrinterView::PrinterView(QWidget *parent)
    :QGraphicsView(parent)
{
    mScene = new QGraphicsScene(this);
    setScene(mScene);
    //mScene->setSceneRect(0,0,width(),height());

    mPlatform = mScene->addRect(0,0,300,300,QPen(QBrush(Qt::black),3),QBrush(Qt::gray));
    mHead = mScene->addEllipse(0,0,20,20,QPen(Qt::red),QBrush(Qt::red));
}

void PrinterView::slotShowPrinter(const PrinterHead& aHead)
{
    static int prevX(0);
    static int prevY(0);
    int x,y,size;
    QColor color;

    x = aHead.mAxises[AXIS_X].mValue;
    y = aHead.mAxises[AXIS_Y].mValue;
    size = aHead.mAxises[AXIS_Z].mValue;
    color = aHead.mColor;

    if((x!=prevX)||(y!=prevY))
    {
        mScene->addLine(prevX,prevY,x,y,QPen(QBrush(color),size/10.0));
        prevX = x;
        prevY = y;
    }
    mHead->setPos(x-10, y-10);
}

void PrinterView::mousePressEvent(QMouseEvent*)
{
    mOldX = cursor().pos().x();
    mOldY = cursor().pos().y();
}

void PrinterView::mouseReleaseEvent(QMouseEvent*)
{
    mOldAngleX = mAngleX;
    mOldAngleZ = mAngleZ;
}

void PrinterView::mouseMoveEvent(QMouseEvent*)
{
    mAngleX = mOldAngleX + (mOldX - cursor().pos().x())/1.0;
    mAngleZ = mOldAngleZ + (mOldY - cursor().pos().y())/1.0;

    applyTransformation();
}

void PrinterView::applyTransformation()
{
    QTransform tr;
    tr.rotate(mAngleZ, Qt::XAxis);
    tr.rotate(mAngleX, Qt::ZAxis);
    setTransform(tr);
}
