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

void MainWindow::slotShowServerInformation(const QString &aInformation, InfoMessageType aType = MT_INFO)
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
    ui->mServerInfoEdit->append(line);
}
