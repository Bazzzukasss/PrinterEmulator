#include "TCPConnection.h"
#include <QTcpSocket>
#include <QHostAddress>

TCPConnection::TCPConnection(QTcpSocket *aSocket, QObject *parent)
    : QObject(parent)
    , mpSocket(aSocket)

{
    connect(mpSocket, &QTcpSocket::readyRead,   this, &TCPConnection::slotReciveHandler);
    connect(mpSocket, &QTcpSocket::connected,   this, &TCPConnection::slotConnected);
    connect(mpSocket, &QTcpSocket::disconnected,this, &TCPConnection::slotDisconnected);
    connect(mpSocket, &QTcpSocket::bytesWritten,this, &TCPConnection::slotBytesWritten);
}

void TCPConnection::slotReciveHandler()
{
    QByteArray buf;
    buf.append( mpSocket->readAll() );

    emit signalInformation(QString("[Received from: %0( id:%1 )]\t%2 bytes").arg(mpSocket->peerAddress().toString()).arg((int)mpSocket).arg(buf.size()) );
    emit signalDataReceived(buf);
}

void TCPConnection::slotConnected()
{
    emit signalInformation("slotConnected");
}

void TCPConnection::slotDisconnected()
{
    emit signalInformation("slotDisconnected");
}

void TCPConnection::slotBytesWritten()
{
    emit signalInformation("slotBytesWritten");
}
