#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMutex>
#include <QHostAddress>
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

    signals:
       void signalCoreConnected();
       void signalCoreDisconnected();
       void signalDataReceived(const QByteArray& aData);
       void signalInformation(const QString& aInformation);

    protected:
       int mPort;
       QHostAddress mIp;
       int mTimeout{default_timeout};
       QTcpSocket *mpSocket;
       QMutex mMutex;

       virtual void handler(const QByteArray &aData);
       virtual void connected();
       virtual void disconnected();
       virtual void bytesWritten(qint64 bytes);

    private:
       bool isConnected;
       void initialize();

};

#endif // TCPCLIENT_H
