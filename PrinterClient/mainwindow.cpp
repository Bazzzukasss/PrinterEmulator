#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
