#ifndef VDS_H
#define VDS_H

#include <QDialog>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"
#include "pureimage.h"

class VisualDownSamplingEffect;
class VisualDownSamplingWidget : public QDialog
{
    Q_OBJECT
public:
    VisualDownSamplingWidget();

    void updateUI()
    {
        rateSS->setValue(rate);
    }

//PARAMETERS
    int rate;
public slots:
    void onRateModified(double v);

private:
    SlideSpiner* rateSS;
    QPushButton* processBtn;

};



class VisualDownSamplingEffect : public PureFilter
{
public:
    VisualDownSamplingEffect(const QString &n);
    virtual ~VisualDownSamplingEffect();

    bool init();

    void process();

    PureEffect* clone()
    {
        VisualDownSamplingEffect* e = new VisualDownSamplingEffect(this->name);
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
                    "Effet DownSample",
                    "Regroupe des zones de pixels\n"
                    "en un seul pixel, pour donner\n"
                    "l'illusion d'une mosaïque."
                    );
    }


private:

    VisualDownSamplingWidget* gemwidget;


};


#endif // GEMPUZZLEEFFECT_H
