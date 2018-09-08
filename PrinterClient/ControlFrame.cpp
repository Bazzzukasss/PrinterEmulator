#include "ControlFrame.h"
#include "ui_ControlFrame.h"
#include <QColorDialog>

ControlFrame::ControlFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ControlFrame)
{
    ui->setupUi(this);
    showColor();
    connect(ui->mButtonDec,   &QPushButton::clicked, this, [&](){ move(-1); });
    connect(ui->mButtonInc,   &QPushButton::clicked, this, [&](){ move(1); });
    connect(ui->mButtonColor, &QPushButton::clicked, this, [&](){ selectColor(); showColor(); });
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
    short int stepsCount = ui->mSpinDistance->value();
    emit signalMove(mId,stepsCount,aDirection,mColor);
}

void ControlFrame::selectColor()
{
    mColor = QColorDialog::getColor();
}

void ControlFrame::showColor()
{
    ui->mButtonColor->setStyleSheet(QString("background-color:%1").arg(mColor.name(QColor::NameFormat::HexArgb)));
}
