#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
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

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&](){
            for(auto frame : mControlFrames)
                mClient.slotSendGetSensorsCommand(frame->getId());
    });
    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotConnectToHost()
{
    mClient.connectToHost( QHostAddress(ui->mLinrEditAddress->text()), ui->mSpinPort->value() );
}

void MainWindow::slotShowInforamtion(const QString &aInformation)
{
    ui->mLog->append(aInformation);
}

void MainWindow::slotShowSensor(int aSensorId, int aSensorValue)
{
    for(auto frame : mControlFrames)
        if(frame->getId() == aSensorId)
            frame->setValue(aSensorValue);
}


