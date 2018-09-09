#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QHostAddress>
#include "Protocol.h"
#include <QMutex>

class QTcpSocket;

class TCPConnection : public QObject
{
    Q_OBJECT
public:
    TCPConnection(QTcpSocket* aSocket, QObject* parent = nullptr);
    QHostAddress getClientAddress() const;
    int getId() const;
    void sendResultAnswer(int aDescription);
    void sendSensorValueAnswer(int aSensorId, int aValue);

signals:
    void signalInformation(const QString& aInformation);
    void signalDataReceived(const QByteArray& aData);    

private slots:
    void slotReciveHandler();
    void slotConnected();
    void slotDisconnected();
    void slotBytesWritten(qint64 aBytes);

private:
    QTcpSocket* mpSocket;
    QMutex mMutex;

    void sendAnswer(const Answer &ans);
};

#endif // TCPCONNECTION_H
