#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "../PrinterServer/Commands.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mControlFrameX->setCaption("X:");
    ui->mControlFrameX->setValue(0);
    ui->mControlFrameX->setId(AXIS_X);

    ui->mControlFrameY->setCaption("Y:");
    ui->mControlFrameY->setValue(0);
    ui->mControlFrameY->setId(AXIS_Y);

    ui->mControlFrameZ->setCaption("Z:");
    ui->mControlFrameZ->setValue(0);
    ui->mControlFrameZ->setId(AXIS_Z);

    connect(ui->mControlFrameX,&ControlFrame::signalMove,this,&MainWindow::slotSendRunMovementCommand);
    connect(ui->mControlFrameY,&ControlFrame::signalMove,this,&MainWindow::slotSendRunMovementCommand);
    connect(ui->mControlFrameZ,&ControlFrame::signalMove,this,&MainWindow::slotSendRunMovementCommand);

    connect(ui->mButtonConnect,&QPushButton::clicked,this,&MainWindow::slotConnectToHost);
    connect(&mClient,&TCPClient::signalInformation,this,[&](const QString& aInformation){ ui->mLog->append(aInformation); });

    slotConnectToHost();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotConnectToHost()
{
    int port(ui->mSpinPort->value());
    QHostAddress address(ui->mLinrEditAddress->text());

    mClient.connectToHost(address,port);
}

void MainWindow::slotSendRunResetCommand()
{

}

void MainWindow::slotSendGetDataCommand()
{

}

void MainWindow::fillData(QByteArray &aByteArray, Command &aCmd)
{
    aByteArray.append((char*)&aCmd, sizeof(Command));
    qDebug()<<sizeof(Command);
    qDebug()<<aByteArray.size();
}

void MainWindow::slotSendRunMovementCommand(int aAxisId, int aDistance, int aColor)
{
    Command cmd;
    cmd.mType = CMD_MOVE;
    cmd.data.cmdMove.mAxisId = aAxisId;
    cmd.data.cmdMove.mDistance = aDistance;
    cmd.data.cmdMove.mColor = aColor;

    QByteArray data;
    fillData(data,cmd);
    qDebug()<<data;

    mClient.sendData(data);
}
