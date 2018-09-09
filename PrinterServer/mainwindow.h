#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TCPServer.h"

struct PrinterHead;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotShowPrinterInformation(const PrinterHead& aHead);
    void slotShowServerInformation(const QString& aInformation, InfoMessageType aType);

private:
    Ui::MainWindow *ui;
    TCPServer mServer;
};

#endif // MAINWINDOW_H
