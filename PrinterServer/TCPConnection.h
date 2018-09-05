#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>

class QTcpSocket;

class TCPConnection : public QObject
{
    Q_OBJECT
public:
    TCPConnection(QTcpSocket* aSocket, QObject* parent = nullptr);

signals:
    void signalInformation(const QString& aInformation);
    void signalDataReceived(const QByteArray& aData);

private slots:
    void slotReciveHandler();
    void slotConnected();
    void slotDisconnected();
    void slotBytesWritten();

private:
    QTcpSocket* mpSocket;
};

#endif // TCPCONNECTION_H
