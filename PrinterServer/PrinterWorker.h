#ifndef PRINTERWORKER_H
#define PRINTERWORKER_H

#include <QObject>
#include "Printer.h"

class PrinterWorker : public QObject
{
    Q_OBJECT
public:
    explicit PrinterWorker(QObject *parent = nullptr);
    void stop();

public slots:
    void slotStart();

private:
    volatile bool isStoped{false};
};

#endif // PRINTERWORKER_H
