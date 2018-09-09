#include "TCPClient.h"
#include <QDebug>
#include <memory>
#include <time.h>

TCPClient::TCPClient(QObject *parent)
    : QObject(parent)
    , mPort(0x0)
    , mIp(QHostAddress::LocalHost)
    , mTimeout(default_timeout)
    , isConnected(false)
{
    initialize();
}

TCPClient::TCPClient(QHostAddress aIp, int aPort, QObject *parent)
    : QObject(parent)
    , mIp(aIp)
    , mPort(aPort)
    , mTimeout(default_timeout)
{
    initialize();
}

TCPClient::~TCPClient()
{}

void TCPClient::reciveHandler()
{
    QByteArray data;

    data.append( mpSocket->readAll() );
    emit signalInformation(QString("[Received]\t%1").arg(data.size()));
    emit signalDataReceived(data);

    dataHandler(data);
}

void TCPClient::connected()
{
    emit signalInformation(QString("[Connected]\t%1\t%2").arg(mIp.toString()).arg(mPort));
}

void TCPClient::disconnected()
{
    mpSocket->deleteLater();
    this->isConnected =false;
    initialize();
    emit signalInformation(QString("[Disconnected]\t%1\t%2").arg(mIp.toString()).arg(mPort));
}

void TCPClient::bytesWritten(qint64 bytes)
{
    emit signalInformation(QString("[Written]\t%1 bytes.").arg(bytes));
}

void TCPClient::initialize()
{
    mpSocket = new QTcpSocket(this);

    connect(mpSocket, &QTcpSocket::readyRead,   this, &TCPClient::reciveHandler);
    connect(mpSocket, &QTcpSocket::connected,   this, &TCPClient::connected);
    connect(mpSocket, &QTcpSocket::disconnected,this, &TCPClient::disconnected);
    connect(mpSocket, &QTcpSocket::bytesWritten,this, &TCPClient::bytesWritten);
}


void TCPClient::slotSendRunMovementCommand(int aAxisId, int aStepsCount, int aDirection, QColor aColor)
{
    Command cmd;
    int r,g,b;

    aColor.getRgb(&r,&g,&b);
    cmd.mType = CMD_MOVE;
    cmd.data.cmdMove.mAxisId = aAxisId;
    cmd.data.cmdMove.mStepsCount = aStepsCount;
    cmd.data.cmdMove.mDirection = aDirection;
    cmd.data.cmdMove.mColorR = r;
    cmd.data.cmdMove.mColorG = g;
    cmd.data.cmdMove.mColorB = b;

    sendCommand(cmd);
}

void TCPClient::slotSendGetSensorsCommand(int aSensorId)
{
    Command cmd;
    cmd.mType = CMD_GET_SENSORS;
    cmd.data.cmdGetSensors.mSensorId = aSensorId;

    sendCommand(cmd);
}

void TCPClient::dataHandler(const QByteArray &aData)
{
    Answer* ans = (Answer*)(aData.data());
    int ansCount = aData.size() / sizeof(Answer);
    do{
        switch(ans->mType)
        {
            case ANS_RESULT:
                    if(ans->data.ansResult.mDescription == RES_CMD_ACCEPTED)
                        emit signalInformation("[Ok] Command accepted.");
                    else
                        emit signalInformation("[Error] Server busy!");
                break;

            case ANS_SENSORS:
                    emit signalShowSensor(ans->data.ansSensors.mId,ans->data.ansSensors.mValue);
                break;
        }
        ++ans;
    }while(--ansCount > 0);
}

void TCPClient::sendCommand(const Command& aCmd)
{
    //QMutexLocker locker(&mMutex);
    QByteArray data;
    data.append((char*)&aCmd, sizeof(Command));
    sendData(data);
}

bool TCPClient::connectToHost(QHostAddress aIp, int aPort, int aTimeout)
{
    mIp = aIp;
    mPort = aPort;
    mTimeout = aTimeout;
    emit signalInformation(QString("[Connecting]\t%1\t%2").arg(mIp.toString()).arg(mPort));

    if(isConnected)
        mpSocket->disconnectFromHost();

    mpSocket->connectToHost(mIp,mPort);
    isConnected = true;
    if(!mpSocket->waitForConnected(mTimeout)){
        emit signalInformation(QString("[Error]\t%1").arg(mpSocket->errorString()));
        isConnected = false;
        return false;
    }

    return true;
}

bool TCPClient::connectToHost(QHostAddress aIp, int aPort)
{
    return connectToHost(aIp,aPort,mTimeout);
}

const char *TCPClient::getSid(){
    static char sid[16] = {0};
    if (sid[0] == 0)
    {
        srand(time(NULL));
        for (int i = 0; i<15; i++)
            sid[i] = ((rand() % 2 == 0) ? ('a' + rand() % ('z' - 'a')) : ('0' + rand() % ('9' - '0')));
    }
    return sid;
}

bool TCPClient::connectToHost()
{
    return connectToHost(mIp,mPort,mTimeout);
}

qint64 TCPClient::sendData(const QByteArray& aData)
{
    if (!this->isConnected){
        emit signalInformation(QString("[Error]\tSocket is not connected."));
        return false;
    }
    bool retval = true;
    emit signalInformation(QString("[Send Data]\t%1").arg(aData.data()));
    qint64 bytesWritten = mpSocket->write(aData);
    mpSocket->flush();
    if( bytesWritten != aData.length() )
    {
        emit signalInformation(QString("[Error]\tFailed to write whole buffer.%1 != %2").arg(bytesWritten).arg(aData.length()));
        retval = false;
    }
    return retval;
}

void TCPClient::setTimeout(int aTimeout)
{
    mTimeout = aTimeout;
}

const QHostAddress TCPClient::getHostAddress() const
{
	return mIp;
}
