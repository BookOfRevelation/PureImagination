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



class VisualCrushEffect : public PureFilter
{
public:
    VisualCrushEffect(const QString &n);
    virtual ~VisualCrushEffect();

    bool init();

    void process();

    PureEffect* clone()
    {
        VisualCrushEffect* e = new VisualCrushEffect(this->name);
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
                    "Effet BitCrush",
                    "Applique un algorithme posté-\n"
                    "risation à une séquence d'image."
                    );
    }


private:

    VisualCrushWidget* gemwidget;


};


#endif // GEMPUZZLEEFFECT_H
