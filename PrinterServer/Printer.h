#ifndef PRINTER_H
#define PRINTER_H

#include <QObject>
#include <QColor>
#include <QVector>
#include <QThread>

class PrinterWorker;

#define pPRINTER Printer::getInstance()

struct PrinterHeadAxis{
    PrinterHeadAxis(int aId = 0, const QString& aName = "Axis") : mId(aId), mName(aName){}
    int mId{0};
    QString mName{"Axis"};
    int mValue{0};
    int mStepsCount{0};
    int mDirection{0};

    bool makeStep(){
        if(mStepsCount>0)
        {
            mValue+=mDirection;
            mStepsCount--;
            return true;
        }
        else
            return false;
    }

    QString getInformation() const{
        return QString("[%0] %1:\t Value: %2\t StepsCount: %3\t Direction: %4").arg(mId).arg(mName).arg(mValue).arg(mStepsCount).arg(mDirection);
    }
};

struct PrinterHead
{
    QVector<PrinterHeadAxis> mAxises;
    QColor mColor{Qt::black};

    bool makeStep(){
        bool isSteps = false;
        for(auto& axis : mAxises)
            isSteps|=axis.makeStep();
        return isSteps;
    }

    QStringList getInformation() const{
        QStringList list;
        for(auto& axis : mAxises)
            list << axis.getInformation() + " \tColor: " + mColor.name(QColor::NameFormat::HexArgb);
        return list;
    }
};

Q_DECLARE_METATYPE(PrinterHead)

class Printer : public QObject
{
    Q_OBJECT
public:
    ~Printer();
    static Printer* getInstance()
    {
        static Printer printer;
        return &printer;
    }

    bool moveHead(int aAxisId, int aStepsCount, int aDirection, QColor aColor);
    int getSensorValue(int aAxisId);
    bool makeStep();

signals:
    void signalStateChanged(const PrinterHead& aHead);
    void signalStartWorker();

private:
    PrinterHead mHead;
    volatile bool mIsBusy{false};
    QThread mWorkerThread;
    PrinterWorker* mpWorker;

    void moving();

    explicit Printer(QObject *parent = nullptr);
    Printer(const Printer&);
    Printer& operator=(const Printer&);
};

#endif // PRINTER_H
