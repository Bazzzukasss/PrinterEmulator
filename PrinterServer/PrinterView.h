#ifndef PRINTERVIEW_H
#define PRINTERVIEW_H

#include <QGraphicsView>

class PrinterHead;

class PrinterView : public QGraphicsView
{
    Q_OBJECT
public:
    PrinterView(QWidget *parent = nullptr);

public slots:
    void slotShowPrinter(const PrinterHead& aHead);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QGraphicsScene* mScene;
    int mOldX;
    int mOldY;
    double mAngleX{-30.0};
    double mAngleZ{60.0};
    double mOldAngleX{-30.0};
    double mOldAngleZ{60.0};

    void applyTransformation();
};

#endif // PRINTERVIEW_H
