#ifndef PUREVIEW_H
#define PUREVIEW_H
#include <QGraphicsView>

class PureView : public QGraphicsView
{
public:
    PureView();

    //zoom
    static constexpr qreal zoomMin = 1.0;
    static constexpr qreal zoomMax = 3.0;
protected:

    void wheelEvent(QWheelEvent* event);
private:
    qreal scaleFactor;
};

#endif // PUREVIEW_H
