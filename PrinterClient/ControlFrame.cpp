#include "ControlFrame.h"
#include "ui_ControlFrame.h"

ControlFrame::ControlFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ControlFrame)
{
    ui->setupUi(this);
    connect(ui->mButtonDec, &QPushButton::clicked, this, [&](){ move(-1); });
    connect(ui->mButtonInc, &QPushButton::clicked, this, [&](){ move(1); });
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

void ControlFrame::setId(int aId)
{
    mId = aId;
}

void ControlFrame::move(int aDirection)
{
    short int distance = ui->mSpinDistance->value() * aDirection;
    char color = ui->mSpinColor->value();
    emit signalMove(mId,distance,color);
}
