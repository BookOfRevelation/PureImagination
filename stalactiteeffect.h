#ifndef STALACTITEEFFECT_H
#define STALACTITEEFFECT_H

#include <QDialog>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"

class StalactiteWidget : public QDialog
{
    Q_OBJECT

public:
    StalactiteWidget();
    void randomize();

    void updateUI()
    {
        thickSS->setValue(thickness);
        varianceSS->setValue(variance);
        pushSS->setValue(push);
    }

    //parameters:
    int thickness;
    int variance;
    int push;

private:

    SlideSpiner* thickSS;
    SlideSpiner* varianceSS;
    SlideSpiner* pushSS;

    QPushButton* processButton;
    QPushButton* randomizeButton;
};

class StalactiteEffect : public PureFilter
{
public:
    StalactiteEffect(const QString& n);
    virtual ~StalactiteEffect();

    bool init();
    void process();

    PureEffect* clone()
    {
        StalactiteEffect* e = new StalactiteEffect(this->name);
        e->setParameters(this->getParameters());
        return e;
    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QWidget* getParamWidget();
    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet Dust",
                    "Brouille l'image en suivant\n"
                    "un décallage de bandes verticales."
                    );
    }

private:
    StalactiteWidget* widget;

};

#endif // STALACTITEEFFECT_H
