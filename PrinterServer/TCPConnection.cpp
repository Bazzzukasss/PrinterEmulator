#include "TCPConnection.h"
#include <QTcpSocket>
#include <QHostAddress>
#include "Commands.h"

TCPConnection::TCPConnection(QTcpSocket *aSocket, QObject *parent)
    : QObject(parent)
    , mpSocket(aSocket)

{
    connect(mpSocket, &QTcpSocket::readyRead,   this, &TCPConnection::slotReciveHandler);
    connect(mpSocket, &QTcpSocket::connected,   this, &TCPConnection::slotConnected);
    connect(mpSocket, &QTcpSocket::disconnected,this, &TCPConnection::slotDisconnected);
    connect(mpSocket, &QTcpSocket::bytesWritten,this, &TCPConnection::slotBytesWritten);
}

QHostAddress TCPConnection::getClientAddress() const
{
    return mpSocket->peerAddress();
}

int TCPConnection::getId() const
{
    return (int)mpSocket;
}

void TCPConnection::sendAnswer(int aAnswer)
{
    Command cmd;
    cmd.mType = CMD_RESULT;
    cmd.data.cmdResult.mDescription = aAnswer;

    QByteArray buf;
    buf.append((char*)&cmd, sizeof(Command));

    mpSocket->write(buf.data());
    mpSocket->flush();
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
    emit signalInformation(QString("[Connected from: %0( id:%1 )]").arg(mpSocket->peerAddress().toString()).arg((int)mpSocket));
}

void TCPConnection::slotDisconnected()
{
    emit signalInformation(QString("[Disconnected from: %0( id:%1 )]").arg(mpSocket->peerAddress().toString()).arg((int)mpSocket));
}

void TCPConnection::slotBytesWritten(qint64 aBytes)
{
    emit signalInformation(QString("[Sended to: %0( id:%1 )]\t%2 bytes").arg(mpSocket->peerAddress().toString()).arg((int)mpSocket).arg(aBytes));
}
