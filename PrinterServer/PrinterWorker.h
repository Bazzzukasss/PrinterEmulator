#ifndef PRINTERWORKER_H
#define PRINTERWORKER_H

#include <QObject>
#include "Printer.h"

class PrinterWorker : public QObject
{
    Q_OBJECT
public:
    explicit PrinterWorker(QObject *parent = nullptr);

public slots:
    void slotStart();
};

#endif // PRINTERWORKER_H
