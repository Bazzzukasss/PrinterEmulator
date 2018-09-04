#include "ControlFrame.h"
#include "ui_ControlFrame.h"

ControlFrame::ControlFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ControlFrame)
{
    ui->setupUi(this);
    connect(ui->mButtonDec, &QPushButton::clicked, this, [&](){ emit signalActivated(makeCMD(-1)); });
    connect(ui->mButtonInc, &QPushButton::clicked, this, [&](){ emit signalActivated(makeCMD(1)); });
}

ControlFrame::~ControlFrame()
{
    delete ui;
}

void ControlFrame::setCaption(const QString &aCaption)
{
    ui->mLabelCption->setText(aCaption);
}

void ControlFrame::setValue(int aValue)
{
    ui->mLabelValue->setText(QString::number(aValue));
}

void ControlFrame::setId(char aId)
{
    mId = aId;
}

unsigned int ControlFrame::makeCMD(int aDirection)
{
    unsigned int cmd;
    short int distance = ui->mSpinDistance->value() * aDirection;
    char color = ui->mSpinColor->value();
    cmd = (mId<<24)||(color<<16)||distance;
    return cmd;
}
