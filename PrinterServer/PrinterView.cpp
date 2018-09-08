#include "PrinterView.h"
#include "Printer.h"
#include <QDebug>

PrinterView::PrinterView(QWidget *parent)
    :QGraphicsView(parent)
{
    mScene = new QGraphicsScene(this);
    setScene(mScene);
    //mScene->setSceneRect(0,0,width(),height());
    applyTransformation();

    mScene->addRect(0,0,200,200);
}

void PrinterView::slotShowPrinter(const PrinterHead& aHead)
{

}



void PrinterView::mousePressEvent(QMouseEvent *event)
{
    mOldX = cursor().pos().x();
    mOldY = cursor().pos().y();
}

void PrinterView::mouseReleaseEvent(QMouseEvent *event)
{
    mOldAngleX = mAngleX;
    mOldAngleZ = mAngleZ;
}

void PrinterView::mouseMoveEvent(QMouseEvent *event)
{
    mAngleX = mOldAngleX + (mOldX - cursor().pos().x())/1.0;
    mAngleZ = mOldAngleZ + (mOldY - cursor().pos().y())/1.0;

    applyTransformation();
    qDebug()<< mAngleX << mAngleZ;
}

void PrinterView::applyTransformation()
{
    QTransform tr;
    tr.rotate(mAngleZ, Qt::XAxis);
    tr.rotate(mAngleX, Qt::ZAxis);
    setTransform(tr);
}
