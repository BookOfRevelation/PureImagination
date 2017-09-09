#ifndef SCROLLEREFFECT_H
#define SCROLLEREFFECT_H

#include <QWidget>
#include "slidespiner.h"
#include <QPushButton>
#include <QCheckBox>
#include <QDialog>
#include "purefilter.h"

class ScrollerEffect;
class ScrollerWidget : public QDialog
{
    Q_OBJECT

public:
    ScrollerWidget();
    void randomize();

    void updateUI()
    {
        percentVSS->setValue(percentV);
        percentHSS->setValue(percentH);
        durationSS->setValue(duration);
    }

//PARAMETERS

    int percentV;
    int percentH;

    int duration;

private:

    SlideSpiner* percentVSS;
    SlideSpiner* percentHSS;
    SlideSpiner* durationSS;

    QPushButton* process;

};



class ScrollerEffect : public PureFilter
{
public:
    ScrollerEffect(const QString& n);
    virtual ~ScrollerEffect();

    bool init();
    void process();

    PureEffect* clone()
    {
        ScrollerEffect* e = new ScrollerEffect(this->name);
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
       return  QPair<QString, QString>(
                    "Effet Scrolling",
                    "Génère une séquence d'image en\n"
                    "décallant verticalement et horizon-\n"
                    "talement les pixels de l'image d'entrée."
                    );
    }

private:

    ScrollerWidget* widget;
};

#endif // SCROLLEREFFECT_H
