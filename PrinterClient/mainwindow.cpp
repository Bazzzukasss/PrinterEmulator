#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mControlFrameX->setCaption("X:");
    ui->mControlFrameX->setValue(0);
    ui->mControlFrameX->setId(1);

    ui->mControlFrameY->setCaption("Y:");
    ui->mControlFrameY->setValue(0);
    ui->mControlFrameY->setId(2);

    ui->mControlFrameZ->setCaption("Z:");
    ui->mControlFrameZ->setValue(0);
    ui->mControlFrameZ->setId(3);

    connect(ui->mControlFrameX,&ControlFrame::signalActivated,this,&MainWindow::slotSendCommand);
    connect(ui->mControlFrameY,&ControlFrame::signalActivated,this,&MainWindow::slotSendCommand);
    connect(ui->mControlFrameZ,&ControlFrame::signalActivated,this,&MainWindow::slotSendCommand);
    connect(ui->mButtonConnect,&QPushButton::clicked,this,&MainWindow::slotConnectToHost);
    connect(&mClient,&NS_Communication::TCPClient::signalInformation,this,[&](const QString& aInformation){ui->mLog->append(aInformation); });

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

void MainWindow::slotSendCommand(unsigned int aCommand)
{
    mClient.sendData(QByteArray::number(aCommand));
}
