#ifndef PRINTERVIEW_H
#define PRINTERVIEW_H

#include <QGraphicsView>

struct PrinterHead;

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
    double mAngleX{0.0};
    double mAngleZ{0.0};
    double mOldAngleX{0.0};
    double mOldAngleZ{0.0};

    void applyTransformation();
    QGraphicsEllipseItem* mHead;
    QGraphicsRectItem* mPlatform;
};

#endif // PRINTERVIEW_H
