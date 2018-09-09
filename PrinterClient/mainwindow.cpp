#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../PrinterServer/Protocol.h"


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

    ui->mControlFrameZ->setCaption("Size:");
    ui->mControlFrameZ->setValue(0);
    ui->mControlFrameZ->setId(AXIS_Z);

    mControlFrames.push_back(ui->mControlFrameX);
    mControlFrames.push_back(ui->mControlFrameY);
    mControlFrames.push_back(ui->mControlFrameZ);

    connect(ui->mControlFrameX, &ControlFrame::signalMove,   &mClient,   &TCPClient::slotSendRunMovementCommand);
    connect(ui->mControlFrameY, &ControlFrame::signalMove,   &mClient,   &TCPClient::slotSendRunMovementCommand);
    connect(ui->mControlFrameZ, &ControlFrame::signalMove,   &mClient,   &TCPClient::slotSendRunMovementCommand);

    connect(ui->mButtonConnect,&QPushButton::clicked,   this,   &MainWindow::slotConnectToHost);
    connect(&mClient,&TCPClient::signalInformation,     this,   &MainWindow::slotShowInforamtion);
    connect(&mClient,&TCPClient::signalShowSensor,      this,   &MainWindow::slotShowSensor);

    slotConnectToHost();

    this->startTimer(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotConnectToHost()
{
    mClient.connectToHost( QHostAddress(ui->mLineEditAddress->text()), ui->mSpinPort->value() );
}

void MainWindow::slotShowInforamtion(const QString &aInformation, InfoMessageType aType)
{
    QString color,brackets;
    switch(aType)
    {
        case MT_INFO:
            color= "#000000";
            brackets = "b";
        break;

        case MT_HINT:
            color= "#333333";
            brackets = "i";
        break;

        case MT_ERROR:
            color= "#ff0000";
            brackets = "b";
        break;

        case MT_OK:
            color= "#0000ff";
            brackets = "b";
        break;

        default:
            color= "#000000";
            brackets = "b";
        break;

    }
    QString line = QString("<%1><font color=%2>%0</font></%1>").arg(aInformation).arg(brackets).arg(color);
    ui->mLog->append(line);
}

void MainWindow::slotShowSensor(int aSensorId, int aSensorValue)
{
    for(auto frame : mControlFrames)
        if(frame->getId() == aSensorId)
            frame->setValue(aSensorValue);
}

void MainWindow::timerEvent(QTimerEvent*)
{
    if(!ui->mCheckBoxSensors->isChecked())
        return;

    for(auto frame : mControlFrames)
        mClient.slotSendGetSensorsCommand(frame->getId());
}
