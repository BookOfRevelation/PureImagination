#ifndef OVCR_H
#define OVCR_H

#include <QDialog>
#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"
#include "pureimage.h"

class OldVcrEffect;
class OldVcrWidget : public QDialog
{
    Q_OBJECT
public:
    OldVcrWidget();

    void randomize();

    void updateUI()
    {
        rateSS->setValue(rate);
        bwSS->setValue(bw);
    }

//PARAMETERS
    int rate;
    int bw;
public slots:
    void onRateModified(double v);
    void onBwModified(double v);

private:
    SlideSpiner* rateSS;
    SlideSpiner* bwSS;
    QPushButton* processBtn;

};



class OldVcrEffect  : public PureFilter
{
public:
    OldVcrEffect(const QString &n);
    virtual ~OldVcrEffect();

    bool init();

    void process();

    PureEffect* clone()
    {
        OldVcrEffect* e = new OldVcrEffect(this->name);
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
                    "Effet OldVcr",
                    "Immite les abérations colorimétriques\n"
                    "des vieux postes de télévisions.\n"
                    "Les paramètres permettent de régler la\n"
                    "hauteur des bandes et leur intensité."
                    );
    }

private:
    OldVcrWidget* gemwidget;


};


#endif // GEMPUZZLEEFFECT_H
