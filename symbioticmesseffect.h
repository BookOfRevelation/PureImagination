#ifndef SYMBIOTICMESSEFFECT_H
#define SYMBIOTICMESSEFFECT_H

#include <QImage>
#include "slidespiner.h"
#include <QPushButton>
#include "purefilter.h"
#include <QDialog>

class SymbioticMessEffect;
class SymbioticMessWidget : public QDialog
{
    Q_OBJECT
public:
    SymbioticMessWidget();

//PARAMETERS
    int rate;
    int chance;
public slots:
    void onRateModified(double v);
    void onChanceModified(double v);

private:

    SlideSpiner* rateSS;
    SlideSpiner* chanceSS;
    QPushButton* processBtn;

};
class SymbioticMessEffect  : public PureFilter
{
public:
    SymbioticMessEffect();
    virtual ~SymbioticMessEffect();
    bool init();
    void process();
    QWidget* getParamWidget();
    PureCore::PureType getOutputType() { return PureCore::Image ;}
    PureCore::PureType getInputType()  { return PureCore::Image ;}
    QPair<QString, QString> getInfo()
    {
        return QPair<QString, QString>(
                    "Effet SymbioticMess",
                    "Applique un algorithme de\n"
                    "bruitage coloré à une \n"
                    "séquence d'images."
                    );
    }

private:
    SymbioticMessWidget* gemwidget;


};

#endif // SYMBIOTICMESSEFFECT_H
