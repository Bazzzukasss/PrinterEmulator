#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMutex>
#include <QHostAddress>
#include "../PrinterServer/Protocol.h"
#include <QColor>

const int default_timeout = 1000;

class TCPClient : public QObject
{
    Q_OBJECT
    public:
        explicit TCPClient(QObject *parent = nullptr);
        explicit TCPClient(QHostAddress aIp, int aPort,QObject *parent = nullptr);
        virtual ~TCPClient();

        bool connectToHost(QHostAddress aIp, int aPort, int aTimeout);
        bool connectToHost(QHostAddress aIp, int aPort);
        bool connectToHost();
        qint64 sendData(const QByteArray& aData);
        void setTimeout(int aTimeout);
        const char *getSid();
        const QHostAddress getHostAddress() const;

    public slots:
       void reciveHandler();
       void slotSendRunMovementCommand(int aAxisId, int aStepsCount, int aDirection, QColor aColor);
       void slotSendGetSensorsCommand(int aSensorId);

    signals:
       void signalCoreConnected();
       void signalCoreDisconnected();
       void signalDataReceived(const QByteArray& aData);
       void signalInformation(const QString& aInformation);
       void signalShowSensor(int aSensorId, int aSensorValue);

    protected:
       int mPort;
       QHostAddress mIp;
       int mTimeout{default_timeout};
       QTcpSocket *mpSocket;

       virtual void dataHandler(const QByteArray &aData);
       virtual void connected();
       virtual void disconnected();
       virtual void bytesWritten(qint64 bytes);
       void sendCommand(const Command& aCmd);

    private:
       bool isConnected;
       void initialize();
       QMutex mMutex;
};

#endif // TCPCLIENT_H
