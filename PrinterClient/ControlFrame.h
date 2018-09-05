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

signals:
    void signalMove(int aId, int aDistance, int aColor);

private:
    Ui::ControlFrame *ui;
    void move(int aDirection);
    int mId{0};
};

#endif // CONTROLFRAME_H
