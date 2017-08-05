#ifndef EFFECTGRAPHICSITEM_H
#define EFFECTGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include "pureeffect.h"
class EffectGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    EffectGraphicsItem(PureEffect* e);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* e);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* e);

    void mousePressEvent(QGraphicsSceneMouseEvent* );

    PureEffect* effect;

signals:
    void overIn(EffectGraphicsItem* item);
    void overOut(EffectGraphicsItem* item);

    void pressedItem(EffectGraphicsItem* item);

private:
    bool hover;


};

#endif // EFFECTGRAPHICSITEM_H
