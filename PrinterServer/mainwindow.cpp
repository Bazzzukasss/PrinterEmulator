#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&mServer,&TCPServer::signalInformation,this,[&](const QString& aInformation){ ui->mLog->append(aInformation); });

    if(!mServer.listen(QHostAddress::Any, 1234))
        ui->mLog->append("[Error]\tServer could not start.");
    else
        ui->mLog->append("Server started.");
}

MainWindow::~MainWindow()
{
    delete ui;
}
