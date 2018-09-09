#include "TCPConnection.h"
#include <QTcpSocket>
#include <QHostAddress>
#include "Protocol.h"

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
    return reinterpret_cast<intptr_t>(mpSocket);
}

void TCPConnection::sendResultAnswer(int aDescription)
{
    Answer ans;
    ans.mType = ANS_RESULT;
    ans.data.ansResult.mDescription = aDescription;

    sendAnswer(ans);
}

void TCPConnection::sendSensorValueAnswer(int aSensorId, int aValue)
{
    Answer ans;
    ans.mType = ANS_SENSORS;
    ans.data.ansSensors.mId = aSensorId;
    ans.data.ansSensors.mValue = aValue;

    sendAnswer(ans);
}

void TCPConnection::slotReciveHandler()
{
    QByteArray buf;
    buf.append( mpSocket->readAll() );

    emit signalInformation(QString("[Received from: %0 ( id:%1 )]\t%2 bytes").arg(mpSocket->peerAddress().toString()).arg(reinterpret_cast<intptr_t>(mpSocket)).arg(buf.size()),MT_HINT);
    emit signalDataReceived(buf);
}

void TCPConnection::slotConnected()
{
    emit signalInformation(QString("[Connected from: %0 ( id:%1 )]").arg(mpSocket->peerAddress().toString()).arg(reinterpret_cast<intptr_t>(mpSocket)),MT_INFO);
}

void TCPConnection::slotDisconnected()
{
    emit signalInformation(QString("[Disconnected : %0 ( id:%1 )]").arg(mpSocket->peerAddress().toString()).arg(reinterpret_cast<intptr_t>(mpSocket)),MT_INFO);
}

void TCPConnection::slotBytesWritten(qint64 aBytes)
{
    emit signalInformation(QString("[Sended to: %0 ( id:%1 )]\t%2 bytes").arg(mpSocket->peerAddress().toString()).arg(reinterpret_cast<intptr_t>(mpSocket)).arg(aBytes),MT_HINT);
}

void TCPConnection::sendAnswer(const Answer &ans)
{
    QMutexLocker locker(&mMutex);
    QByteArray data;
    data.append((char*)&ans, sizeof(Answer));

    mpSocket->write(data);
    mpSocket->flush();
}
