#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TCPClient.h"

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
    void slotConnectToHost();
    void slotSendCommand(unsigned int aCommand);

private:
    Ui::MainWindow *ui;
    NS_Communication::TCPClient mClient;
};

#endif // MAINWINDOW_H
