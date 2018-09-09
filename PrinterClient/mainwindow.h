#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TCPClient.h"
#include "../PrinterServer/Protocol.h"

class ControlFrame;

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
    void slotShowInforamtion(const QString& aInformation, InfoMessageType aType = MT_INFO);
    void slotShowSensor(int aSensorId, int aSensorValue);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    Ui::MainWindow *ui;
    TCPClient mClient;
    QVector<ControlFrame*> mControlFrames;
};

#endif // MAINWINDOW_H
