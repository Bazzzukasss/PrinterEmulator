#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TCPClient.h"
#include "../PrinterServer/Commands.h"

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
    void slotSendRunMovementCommand(int aAxisId, int aStepsCount, int aDirection, QColor aColor);
    void slotSendRunResetCommand();
    void slotSendGetDataCommand();

private:
    Ui::MainWindow *ui;
    TCPClient mClient;

    void fillData(QByteArray& aByteArray, Command &aCmd);
};

#endif // MAINWINDOW_H
