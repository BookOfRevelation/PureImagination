#ifndef PURESCENE_H
#define PURESCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include "pureeffect.h"
#include "effectgraphicsitem.h"
#include <QCoreApplication>
class PureScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PureScene();

    PureEffect *addEffect(PureEffect* e);
    void removeEffect(PureEffect* e);

    void run();

    void clean();



protected:
    void hoverInEffect(EffectGraphicsItem* e);
    void hoverOutEffect(EffectGraphicsItem* e);


signals:

    void makeProgress(int cur, int max);
    void endChain(bool success);


private:

    static constexpr int marginRight = 10;
    QVector<QPair<QPair<EffectGraphicsItem*, QGraphicsTextItem*>, PureEffect*>> eitems;

    QGraphicsItem* hovered;

    int curWidth;


    void combinePuzzle(int from);

    void replacePuzzle();


};

#endif // PURESCENE_H
