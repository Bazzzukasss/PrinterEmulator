#include "TCPServer.h"
#include "TCPConnection.h"
#include "Commands.h"
#include <QTcpSocket>
#include "Printer.h"

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

    emit signalInformation(QString("[Connected: %0( id:%1 )]").arg(pConnection->getClientAddress().toString()).arg((int)pConnection->getId()) );
}

void TCPServer::slotDataHandler(const QByteArray &aData)
{
    bool result(false);
    TCPConnection* pConnection = qobject_cast<TCPConnection*>(sender());
    Command* cmd = (Command*)(aData.data());
    switch(cmd->mType)
    {
        case CMD_GET:
            break;
        case CMD_SET:
            break;
        case CMD_MOVE:
            result = pPRINTER->moveHead(
                                        cmd->data.cmdMove.mAxisId,
                                        cmd->data.cmdMove.mStepsCount,
                                        cmd->data.cmdMove.mDirection,
                                        QColor(cmd->data.cmdMove.mColorR,cmd->data.cmdMove.mColorG,cmd->data.cmdMove.mColorB)
                                      );
            break;
    }
    if(result)
        pConnection->sendAnswer(1);
    else
        pConnection->sendAnswer(0);
}
