#ifndef VCE_H
#define VCE_H

#include <QDialog>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"

class VisualCrushEffect;
class VisualCrushWidget : public QDialog
{
    Q_OBJECT
public:
    VisualCrushWidget();

//PARAMETERS
    int rate;
public slots:
    void onRateModified(double v);



private:
    SlideSpiner* rateSS;
    QPushButton* processBtn;

};



class VisualCrushEffect : public PureFilter
{
public:
    VisualCrushEffect();
    virtual ~VisualCrushEffect();

    bool init();

    void process();

    QWidget* getParamWidget();

    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}

    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet BitCrush",
                    "Applique un algorithme posté-\n"
                    "risation à une séquence d'image."
                    );
    }


private:

    VisualCrushWidget* gemwidget;


};


#endif // GEMPUZZLEEFFECT_H
