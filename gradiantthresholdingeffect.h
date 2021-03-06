#ifndef GRADIANTTHRESHOLDINGEFFECT_H
#define GRADIANTTHRESHOLDINGEFFECT_H


#include <QWidget>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"

class GradiantThresholdingEffect;
class GradiantThresholdingWidget : public QWidget
{
    Q_OBJECT
public:
    GradiantThresholdingWidget(GradiantThresholdingEffect* effect);

    void updateUI()
    {
        seuilSS->setValue(seuil);
    }

//PARAMETERS
    int seuil;

public slots:
    void onSeuilModified(double v);


private:
    GradiantThresholdingEffect* burgle;

    SlideSpiner* seuilSS;


    QPushButton* processBtn;

};



class GradiantThresholdingEffect : public PureFilter
{
public:
    GradiantThresholdingEffect(const QString &n);
    virtual ~GradiantThresholdingEffect();

    bool init();

    void process();

//    PureEffect* clone()
//    {
//        //GradiantThresholdingEffect* e = new GradiantThresholdingEffect(this->name);
//        //e->setParameters(this->getParameters());
//        return e;
//    }

    void setParameters(QVector<QVariant> p);
    QVector<QVariant> getParameters() const;

    QWidget* getParamWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

private:

    bool sequence;
    QString targetDir;
    QVector<QPair<QImage, QString>> baseImages;

    QVector<QImage> resultImages;

    GradiantThresholdingWidget* gemwidget;


};
#endif // GRADIANTTHRESHOLDINGEFFECT_H
