#ifndef IMAGETOFRAGMENT_H
#define IMAGETOFRAGMENT_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QDialog>
#include "puretransformater.h"
#include "slidespiner.h"

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

class FragmentView : public QGraphicsView
{
public:
    FragmentView();

    void init();

    QGraphicsRectItem* selection;

    void setSelSize(int c)
    {
        size = c;
    }
    int size;
    virtual void mouseMoveEvent(QMouseEvent* e);
};

class FragmentWidget : public QDialog
{
public:
    FragmentWidget();
    void init()
    {
        view->init();
    }

private:
    FragmentView* view;
    SlideSpiner* selectionSS;
};

class ImageToFragment : public PureTransformater
{
public:
    ImageToFragment(const QString& n);
    ~ImageToFragment();

    bool init();
    void process();

    PureEffect* clone()
    {
        ImageToFragment* e = new ImageToFragment(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
       return  QPair<QString, QString>(
                    "Image to fragment",
                    "Ne considère qu'une partie de l'image d'entrée."
                    );
    }

    QWidget* getParamWidget()
    {
        return widget;
    }

private:
    FragmentWidget* widget;
};

#endif // IMAGETOFRAGMENT_H
