#ifndef PRINTER_H
#define PRINTER_H

#include <QObject>
#include <QColor>

#define pPRINTER Printer::getInstance();

struct PrinterHeadAxis{
    int mValue{0};
    int mStepsCount{0};
    int mDirection{0};
    void makeStep(){
        if(--mStepsCount>0)
            mValue+=mDirection;
    }
};

struct PrinterHead
{
    QVector<PrinterHeadAxis> mAxises;
    QColor mColor{Qt::black};
    void makeStep(){
        for(auto& axis : mAxises)
            axis.makeStep();
    }
};

Q_DECLARE_METATYPE(PrinterHead)


class Printer : public QObject
{
    Q_OBJECT
public:
    static Printer* getInstance()
    {
        static Printer printer;
        return &printer;
    }

    bool moveHead(int aAxisId, int aStepsCount, int aDirection, int aColor);
    int getCurrentPosition(int aAxisId);

signals:
    void signalStateChanged(const PrinterHead& aPrintHead);

private:
    PrinterHead mHead;
    volatile bool mIsBusy{false};

    void startMotion();
    void stopMotion();
    void moving();
    void initialize();

    explicit Printer(QObject *parent = nullptr){}
    Printer(const Printer&);
    Printer& operator=(const Printer&);
};

#endif // PRINTER_H
