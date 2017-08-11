#include "effectgraphicsitem.h"
#include <QGraphicsSceneMouseEvent>
EffectGraphicsItem::EffectGraphicsItem(PureEffect* e)
    :QObject(), QGraphicsPixmapItem(), effect(e), hover(false)
{
   this->setAcceptHoverEvents(true);
}

void EffectGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    QGraphicsItem::hoverEnterEvent(e);
    hover = true;
    emit overIn(this);



}


void EffectGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    QGraphicsItem::hoverLeaveEvent(e);
    hover = false;
    emit overOut(this);

}

void EffectGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent * e)
{
    if(hover && e->button() == Qt::LeftButton)
    {
        emit pressedItem(this);
    }
}
