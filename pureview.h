#ifndef PUREVIEW_H
#define PUREVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
class PureView : public QGraphicsView
{
public:
    PureView();

    //zoom
    static constexpr qreal zoomMin = 0.2;
    static constexpr qreal zoomMax = 6.0;
protected:

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
private:
    qreal scaleFactor;
    bool translating;
};

#endif // PUREVIEW_H
