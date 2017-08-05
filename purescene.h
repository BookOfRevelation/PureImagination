#ifndef PURESCENE_H
#define PURESCENE_H

#define SPACING  10
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>

#include "pureeffect.h"
#include "effectgraphicsitem.h"

class PureScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PureScene();

    void addEffect(PureEffect* e);

    void run();

    void clean();



protected:
    void hoverInEffect(EffectGraphicsItem* e);
    void hoverOutEffect(EffectGraphicsItem* e);


signals:

    void makeProgress(int cur, int max);
    void endChain(bool success);


private:
    QVector<QPair<EffectGraphicsItem*, PureEffect*>> eitems;

    QGraphicsItem* hovered;



};

#endif // PURESCENE_H
