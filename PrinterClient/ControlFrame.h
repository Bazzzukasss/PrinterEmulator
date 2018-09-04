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
    void setId(char aId);

signals:
    void signalActivated(unsigned int aCommand);

private:
    Ui::ControlFrame *ui;
    unsigned int makeCMD(int aDirection);
    int mId{0};
};

#endif // CONTROLFRAME_H
