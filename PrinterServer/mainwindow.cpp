#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Printer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&mServer, &TCPServer::signalInformation,    this,       &MainWindow::slotShowServerInformation);
    connect(pPRINTER, &Printer::signalStateChanged,     this,       &MainWindow::slotShowPrinterInformation);
    connect(pPRINTER, &Printer::signalStateChanged,     ui->mView,  &PrinterView::slotShowPrinter);

    if(!mServer.listen(QHostAddress::Any, 1234))
        ui->mServerInfoEdit->append("[Error]\tServer could not start.");
    else
        ui->mServerInfoEdit->append("Server started.");

    pPRINTER->moveHead(0,20,1,Qt::blue);
    pPRINTER->moveHead(1,20,-1,Qt::blue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotShowPrinterInformation(const PrinterHead &aHead)
{
    ui->mPrinterInfoEdit->clear();
    for(auto& str : aHead.getInformation())
        ui->mPrinterInfoEdit->append( str );
}

void MainWindow::slotShowServerInformation(const QString &aInformation)
{
    ui->mServerInfoEdit->append(aInformation);
}
