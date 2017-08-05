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
    VisualDownSamplingEffect();
    virtual ~VisualDownSamplingEffect();

    bool init();

    void process();

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
