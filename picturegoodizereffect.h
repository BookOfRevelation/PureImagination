#ifndef PICTUREGOODIZEREFFECT_H
#define PICTUREGOODIZEREFFECT_H

#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"
#include <QDialog>

class PictureGoodizerWidget : public QDialog
{
public:
    PictureGoodizerWidget();
    void randomize();
    void updateUI()
    {
        powerSS->setValue(power);
        veloSS->setValue(velocity);
    }

    int power;
    float velocity;

private:
    SlideSpiner* powerSS;
    SlideSpiner* veloSS;

    QPushButton* processBtn;
    QPushButton* randomBtn;
};

class PictureGoodizerEffect : public PureFilter
{
public:
    PictureGoodizerEffect(const QString &n);
    virtual ~PictureGoodizerEffect();

    bool init();
    void process();

    PureEffect* clone()
    {
        PictureGoodizerEffect* e = new PictureGoodizerEffect(this->name);
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
                    "Effet Goodizer",
                   ""
                    );
    }

private:

    PictureGoodizerWidget* widget;
};

#endif // PICTUREGOODIZEREFFECT_H
