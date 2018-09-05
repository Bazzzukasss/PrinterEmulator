#include "TCPServer.h"
#include "TCPConnection.h"
#include "Commands.h"

TCPServer::TCPServer(QObject *parent)
    : QTcpServer(parent)
{
    connect(this, &TCPServer::newConnection, this, &TCPServer::slotNewConnection);
}

void TCPServer::slotNewConnection()
{
    TCPConnection *pConnection = new TCPConnection( nextPendingConnection(), this);

    connect(pConnection,&TCPConnection::signalInformation,  this, &TCPServer::signalInformation );
    connect(pConnection,&TCPConnection::signalDataReceived, this ,&TCPServer::slotDataHandler );
}

void TCPServer::slotDataHandler(const QByteArray &aData)
{

}
