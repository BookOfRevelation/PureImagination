#include "purescene.h"
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsOpacityEffect>
#include <QGraphicsTextItem>
#include <QDesktopServices>
#include <QUrl>

PureScene::PureScene()
    : QGraphicsScene()
{

    hovered = nullptr;
    curWidth = 0;
}


void PureScene::clean()
{
    this->clear();
    eitems.clear();
    hovered = nullptr;
    curWidth = 0;

}

PureEffect* PureScene::addEffect(PureEffect *ev)
{
    PureEffect* e = ev->clone();
        PureCore::PureNature n = e->getNature();
        QString file;
        switch(n)
        {
        case PureCore::Loader:
            file = "loader";
            break;
        case PureCore::Filter:
            file = "filter";
            break;
        case PureCore::Transformater:
            file = "transformater";
            break;
        case PureCore::Saver:
            file = "saver";
            break;
        }

        QString type;
        PureCore::PureType t = e->getInputType();
        if(t == PureCore::NoType)
        {
            t = e->getOutputType();
        }

        switch(t)
        {
        case PureCore::Image:
            type = "-img-e";
            break;
        default:
            type = "";
            break;
        }

        QPixmap pm(QString(":/res/effects/Puzzle-%1.png").arg(file));

        EffectGraphicsItem* pitem = new EffectGraphicsItem(e);
        pitem->setPixmap(pm);

        this->addItem(pitem);
        pitem->setPos(curWidth, 0.0);


        QGraphicsTextItem* tit = this->addText(e->name);
        tit->setDefaultTextColor(Qt::white);
        tit->setPos(curWidth, pm.height()-25);


        curWidth = curWidth + marginRight + pm.width();

        connect(pitem, &EffectGraphicsItem::overIn, this, &PureScene::hoverInEffect);
        connect(pitem, &EffectGraphicsItem::overOut, this, &PureScene::hoverOutEffect);
        connect(pitem, &EffectGraphicsItem::pressedItem, this, [this](EffectGraphicsItem* e)
        {
           e->effect->init();
        });
        eitems.push_back(QPair<QPair<EffectGraphicsItem*, QGraphicsTextItem*>, PureEffect*>(QPair<EffectGraphicsItem*, QGraphicsTextItem*>(pitem, tit), e));

        return e;

}

void PureScene::removeEffect(PureEffect *e)
{
    bool notFound = true;
    for(int i = eitems.count() -1 ; i >= 0  && notFound; --i)
    {
        QGraphicsItem* it = nullptr;
        QGraphicsTextItem* tit = nullptr;
        if(eitems[i].first.first->effect->name == e->name)
        {
            it = eitems[i].first.first;
            tit = eitems[i].first.second;
            eitems.remove(i);

            this->removeItem(it);
            this->removeItem(tit);
            QGraphicsPixmapItem* pit = static_cast<QGraphicsPixmapItem*>(it);
            curWidth = curWidth - marginRight - pit->pixmap().width();

            delete it;
            delete tit;
            notFound = false;
        }

    }
}

void PureScene::run()
{
    bool runable = false;
    if(eitems.count()>=2)
    {
        PureEffect* first = eitems.first().second;
        PureEffect* last = eitems.last().second;
        runable = (first->getNature() == PureCore::Loader && last->getNature() == PureCore::Saver);
    }

    if(runable)
    {
        int current = 0;
        int max = 2* eitems.count();
        for(int i = 0 ; i < eitems.count() ; ++i)
        {
            PureEffect* e = eitems[i].second;
            if(e->getNature() == PureCore::Loader || e->getNature() == PureCore::Saver)
            {
                current = current + 2;
                e->process();
                emit makeProgress(current, max);
            }
            else
            {
                current = current + 1;
                emit makeProgress(current, max);

                //process the effect
                current = current + 1;
                e->process();
                emit makeProgress(current, max);

            }
        }
        if(QMessageBox::information(nullptr, "Success", "Processing suceeded.", QMessageBox::Ok | QMessageBox::Open) == QMessageBox::Open)
        {
           QDesktopServices::openUrl(QUrl(PureCore::lastTargetDir));
        }
    }
    else
    {
        QMessageBox::critical(nullptr, "Error", "The processing chain must start with a loader and end with a saver.");
    }


}


void PureScene::hoverInEffect(EffectGraphicsItem* e)
{
    QGraphicsOpacityEffect* noEffect = new QGraphicsOpacityEffect();
    noEffect->setOpacity(1.0);

    QGraphicsColorizeEffect* holder = new QGraphicsColorizeEffect();
    holder->setColor(QColor(212,144,184,200));

    if(hovered)
    {
        hovered->setGraphicsEffect(noEffect);
        hovered = nullptr;
    }

    //enlight the item
    hovered = e;
    hovered->setGraphicsEffect(holder);

}

void PureScene::hoverOutEffect(EffectGraphicsItem *e)
{
    QGraphicsOpacityEffect* noEffect = new QGraphicsOpacityEffect();
    noEffect->setOpacity(1.0);
    e->setGraphicsEffect(noEffect);
    hovered = nullptr;

}

