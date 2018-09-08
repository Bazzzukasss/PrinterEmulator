#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TCPClient.h"
#include "../PrinterServer/Commands.h"

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
    void slotShowInforamtion(const QString& aInformation);
    void slotShowSensor(int aSensorId, int aSensorValue);

private:
    Ui::MainWindow *ui;
    TCPClient mClient;
    QVector<ControlFrame*> mControlFrames;


};

#endif // MAINWINDOW_H
