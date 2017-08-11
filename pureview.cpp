#include "pureview.h"

#include <QWheelEvent>
#include <QScrollBar>
#include <QFileDialog>
#include "pureconfiguration.h"

PureView::PureView()
    : QGraphicsView()
{
    translating = false;
    scaleFactor = 1.0;
    setStyleSheet(QString("background-image: url(%1);").arg(PureConfiguration::bgName));
}


void PureView::wheelEvent(QWheelEvent *event)
{
        //compute the wheel point
        const QPointF p0scene = mapToScene(event->pos());


        //set the factor
        qreal factor = (std::pow(1.2, event->delta()/240.0));
        qreal newscale = scaleFactor * factor;



        //accept zoom or dezoom
        if(newscale <= PureView::zoomMax && newscale >= PureView::zoomMin)
        {
            scaleFactor = newscale;
            scale(factor,factor);


            //place the camera on the zoom point
            const QPointF p1mouse = mapFromScene(p0scene);
            const QPointF move = p1mouse - event->pos();

            horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
            verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());
        }
}

void PureView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    if(event->button() == Qt::MidButton)
    {
        translating = true;
    }
}

void PureView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    translating = false;
}

void PureView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if(translating)
    {
        int x = event->x();
        int y = event->y();

        this->centerOn(x,y);

    }
}


void PureView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                          "/home",
                                                          tr("Images (*.png *.xpm *.jpg *.gif)"));
        if(fileName != "")
        {
            this->setStyleSheet(QString("background-image: url(%1);").arg(fileName));
        }

        PureConfiguration::bgName = fileName;
    }

}
