#ifndef CONTROLFRAME_H
#define CONTROLFRAME_H

#include <QFrame>

namespace Ui {
class ControlFrame;
}

class ControlFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ControlFrame(QWidget *parent = 0);
    ~ControlFrame();

    void setCaption(const QString& aCaption);
    void setValue(int aValue);
    void setId(int aId);
    int getId();

signals:
    void signalMove(int aAxisId, int aStepsCount, int aDirection, QColor aColor);

private:
    Ui::ControlFrame *ui;
    void move(int aDirection);
    void selectColor();
    void showColor();
    int mId{0};
    QColor mColor{Qt::blue};
};

#endif // CONTROLFRAME_H
