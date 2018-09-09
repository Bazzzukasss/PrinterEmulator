#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <TCPConnection.h>

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);

signals:
    void signalInformation(const QString& aInformation, InfoMessageType aType = MT_INFO);

private slots:
    void slotNewConnection();
    void slotDataHandler(const QByteArray& aData);
};

#endif // TCPSERVER_H
